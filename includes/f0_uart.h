#ifndef F0_UART_H
#define F0_UART_H

#include <string>
#include "i_uart.h"
#include "f0_uart_memory.h"

class F0Uart : public IUart {
public:
  explicit F0Uart(uintptr_t uart_addr, IRcc *rcc) {
    uart_memory = reinterpret_cast<F0UartMemory *>(uart_addr);
    Rcc_Uart uart = Rcc_Uart::NONE;
    if (uart_memory == reinterpret_cast<F0UartMemory *>(USART1))
      uart = Rcc_Uart::UART1;
    else if (uart_memory == reinterpret_cast<F0UartMemory *>(USART2))
      uart = Rcc_Uart::UART2;

    system_core_clock = rcc->get_system_core_clock();
    rcc->enable_and_reset_uart(uart);
  }
  ~F0Uart() = default;

  void send_char(char data) override { uart_memory->send_char(data); }
  void send_string(std::string string) override { uart_memory->send_string(string); }
  void clear_screen() override { uart_memory->clear_screen(); }
  void init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate, Uart_Mode mode) override {
    init(parity, stop_bit, baudrate, mode, 0);
  }
  void init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate, Uart_Mode mode, uint32_t priority) override {
    uart_memory->init(parity, stop_bit, baudrate, system_core_clock);
    if (mode == Uart_Mode::INTERRUPT)
      enable_interrupts(priority);
  }

private:
  F0UartMemory *uart_memory;
  uint32_t system_core_clock;
  void enable_interrupts(uint32_t priority) {
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
};

#endif //F0_UART_H
