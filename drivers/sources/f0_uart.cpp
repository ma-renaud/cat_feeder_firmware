#include "f0_uart.h"

F0Uart::F0Uart(uintptr_t uart_addr, IRcc *rcc) {
  uart_memory = reinterpret_cast<F0UartMemory *>(uart_addr);
  Rcc_Uart uart = Rcc_Uart::NONE;
  if (uart_memory == reinterpret_cast<F0UartMemory *>(USART1))
    uart = Rcc_Uart::UART1;
  else if (uart_memory == reinterpret_cast<F0UartMemory *>(USART2))
    uart = Rcc_Uart::UART2;

  system_core_clock = rcc->get_system_core_clock();
  rcc->enable_and_reset_uart(uart);
}

void F0Uart::init(Uart_Parity parity,
                  Uart_Stop_Bit stop_bit,
                  Uart_Baudrate baudrate,
                  Uart_Mode mode,
                  uint32_t priority) {
  uart_memory->init(parity, stop_bit, baudrate, system_core_clock);
  if (mode == Uart_Mode::INTERRUPT)
    enable_interrupts(priority);
}

void F0Uart::send_byte(uint8_t data) {
  buf_tx.push(data);
  uart_memory->enable_tx_interrupt();
}

void F0Uart::send_string(std::string string) {
  for (auto & c : string) {
    send_byte(c);
  }
}

uint8_t F0Uart::get_byte() {
  return EOF;
}

void F0Uart::clear_screen() {
  send_byte(27);
  send_byte('[');
  send_byte('H');
  send_byte(27);
  send_byte('[');
  send_byte('J');
}

void F0Uart::enable_interrupts(uint32_t priority) {
  uart_memory->enable_interrupts();

  IRQn_Type irqn = HardFault_IRQn;
  if (uart_memory == reinterpret_cast<F0UartMemory *>(Uart_Peripheral::UART1))
    irqn = USART1_IRQn;
  else if (uart_memory == reinterpret_cast<F0UartMemory *>(Uart_Peripheral::UART2))
    irqn = USART2_IRQn;

  if (irqn == USART1_IRQn || irqn == USART2_IRQn) {
    NVIC_EnableIRQ(irqn);
    NVIC_SetPriority(irqn, priority);
  }
}

void F0Uart::IRQHandler() {
  static uint8_t data;
  if (uart_memory->is_rx_interrupt()) {
    buf_rx.push(uart_memory->interrupt_get());
  }
  if (uart_memory->is_tx_interrupt()) {
    if (buf_tx.size() > 0) {
      buf_tx.pop(data);
      uart_memory->interrupt_send(data);
    } else {
      uart_memory->disable_tx_interrupt();
    }
  }

  uart_memory->manage_overrun();
}