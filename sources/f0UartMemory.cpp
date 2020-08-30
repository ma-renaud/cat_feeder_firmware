#include "f0UartMemory.h"
#include "stm32f0xx.h"

CircularBuffer<unsigned char, 32> buf_tx;
CircularBuffer<unsigned char, 32> buf_rx;

void F0UartMemory::init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate) {
  set_parity(parity);
  set_stop_bit(stop_bit);
  set_baudrate(baudrate);
  CR1 |= (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE);
}

void F0UartMemory::enable_interrupts(uint32_t priority) {
  CR1 |= (USART_CR1_TXEIE | USART_CR1_RXNEIE);

  IRQn_Type irqn = HardFault_IRQn;
  if (this == reinterpret_cast<F0UartMemory *>(USART1))
    irqn = USART1_IRQn;
  else if (this == reinterpret_cast<F0UartMemory *>(USART2))
    irqn = USART2_IRQn;

  if (irqn == USART1_IRQn || irqn == USART2_IRQn) {
    NVIC_EnableIRQ(irqn);
    NVIC_SetPriority(irqn, priority);
  }
}

void F0UartMemory::send_char(char data) {
  buf_tx.push(data);
  CR1 |= USART_CR1_TXEIE; // Interrupt transmit activation
}

void F0UartMemory::send_string(std::string string) {
  int iCpt = 0;
  for (char & c : string) {
    send_char(c);
  }
}

void F0UartMemory::clear_debug_screen() {
  send_char(27);
  send_char('[');
  send_char('H');
  send_char(27);
  send_char('[');
  send_char('J');
}

void F0UartMemory::set_parity(Uart_Parity parity) {
  if (parity != Uart_Parity::NONE) {
    CR1 |= USART_CR1_PCE;

    if (parity == Uart_Parity::ODD)
      CR1 |= USART_CR1_PS;
    else
      CR1 &= ~(USART_CR1_PS);
  } else {
    CR1 &= ~(USART_CR1_PCE);
  }
}

void F0UartMemory::set_stop_bit(Uart_Stop_Bit stop_bit) {
  if (stop_bit == Uart_Stop_Bit::TWO_BITS)
    CR2 |= USART_CR2_STOP_1;
  else if (stop_bit == Uart_Stop_Bit::ONE_AND_HALF_BITS)
    CR2 |= USART_CR2_STOP;
  else
    CR2 &= ~(USART_CR2_STOP);
}

void F0UartMemory::set_baudrate(Uart_Baudrate baudrate) {
  BRR = (uint16_t) (SystemCoreClock / static_cast<uint32_t>(baudrate));
}

/*Interruption USART2*/
#ifdef __cplusplus
extern "C" {
#endif
void USART2_IRQHandler(void) {
  static uint8_t data;
  if ((USART2->ISR & USART_ISR_RXNE) == USART_ISR_RXNE) {
    buf_rx.push((uint8_t)USART2->RDR);
  }
  if ((USART2->ISR & USART_ISR_TXE) == USART_ISR_TXE) {
    if (buf_tx.size() > 0) {
      buf_tx.pop(data);
      USART2->TDR = (uint16_t) (data);
    } else {
      USART2->CR1 &= ~USART_CR1_TXEIE; // Desactivate interuption if nothing is sent
    }
  }

  if ((USART2->ISR & USART_ISR_ORE) == USART_ISR_ORE) {
    USART2->ICR |= USART_ICR_ORECF;
  }
}
#ifdef __cplusplus
}
#endif