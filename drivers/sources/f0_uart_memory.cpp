#include "../includes/f0_uart_memory.h"
#include "stm32f0xx.h"

CircularBuffer<unsigned char, 32> buf_tx;
CircularBuffer<unsigned char, 32> buf_rx;

enum class CR1: uint32_t {
  UE      = 0x01U,
  RE      = 0x04U,
  TE      = 0x08U,
  TXEIE   = 0x80U,
  RXNEIE  = 0x20U,
  PS      = 0x200U,
  PCE     = 0x400U
};

enum class CR2: uint32_t {
  STOP_1  = 0x2000U,
  STOP    = 0x3000U
};

enum class ISR: uint32_t {
  ORE   = 0x08U,
  RXNE  = 0x20U,
  TXE   = 0x80U
};

enum class ICR: uint32_t {
  ORECF   = 0x08U
};

void F0UartMemory::init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate, uint32_t system_core_clock) {
  set_parity(parity);
  set_stop_bit(stop_bit);
  set_baudrate(baudrate, system_core_clock);
  enable_uart();
}

void F0UartMemory::enable_interrupts() {
  CR1 |= (to_underlying(CR1::TXEIE) | to_underlying(CR1::RXNEIE));
}

void F0UartMemory::send_char(char data) {
  buf_tx.push(data);
  CR1 |= to_underlying(CR1::TXEIE); // Interrupt transmit activation
}

void F0UartMemory::send_string(const std::string& string) {
  for (auto & c : string) {
    send_char(c);
  }
}

void F0UartMemory::clear_screen() {
  send_char(27);
  send_char('[');
  send_char('H');
  send_char(27);
  send_char('[');
  send_char('J');
}

void F0UartMemory::set_parity(Uart_Parity parity) {
  if (parity != Uart_Parity::NONE) {
    CR1 |= to_underlying(CR1::PCE);

    if (parity == Uart_Parity::ODD)
      CR1 |= to_underlying(CR1::PS);
    else
      CR1 &= ~(to_underlying(CR1::PS));
  } else {
    CR1 &= ~(to_underlying(CR1::PCE));
  }
}

void F0UartMemory::set_stop_bit(Uart_Stop_Bit stop_bit) {
  if (stop_bit == Uart_Stop_Bit::TWO_BITS)
    CR2 |= to_underlying(CR2::STOP_1);
  else if (stop_bit == Uart_Stop_Bit::ONE_AND_HALF_BITS)
    CR2 |= to_underlying(CR2::STOP);
  else
    CR2 &= ~(to_underlying(CR2::STOP));
}

void F0UartMemory::set_baudrate(Uart_Baudrate baudrate, uint32_t system_core_clock) {
  BRR = (uint16_t) (system_core_clock / static_cast<uint32_t>(baudrate));
}

void F0UartMemory::enable_uart() {
  CR1 |= (to_underlying(CR1::UE) | to_underlying(CR1::RE) | to_underlying(CR1::TE));
}

/*Interruption USART2*/
void F0UartMemory::IRQHandler() {
  static uint8_t data;
  if ((ISR & to_underlying(ISR::RXNE)) == to_underlying(ISR::RXNE)) {
    buf_rx.push((uint8_t)RDR);
  }
  if ((ISR & to_underlying(ISR::TXE)) == to_underlying(ISR::TXE)) {
    if (buf_tx.size() > 0) {
      buf_tx.pop(data);
      TDR = (uint16_t) (data);
    } else {
      CR1 &= ~(to_underlying(CR1::TXEIE)); // Desactivate interuption if nothing is sent
    }
  }

  if ((ISR & to_underlying(ISR::ORE)) == to_underlying(ISR::ORE)) {
    ICR |= to_underlying(ICR::ORECF);
  }
}