#ifndef F0_UART_H
#define F0_UART_H

#include <string>
#include "i_uart.h"
#include "f0_uart_memory.h"

class F0Uart : public IUart {
public:
  explicit F0Uart(uintptr_t uart_addr) {
    uart_memory = reinterpret_cast<F0UartMemory *>(uart_addr);
  }
  ~F0Uart() = default;

  void send_char(char data) override { uart_memory->send_char(data); }
  void send_string(std::string string) override { uart_memory->send_string(string); }
  void clear_debug_screen() override { uart_memory->clear_debug_screen(); }
  void init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate) override { uart_memory->init(parity, stop_bit, baudrate); }
  void enable_interrupts(uint32_t priority) override { uart_memory->enable_interrupts(priority); }

private:
  F0UartMemory *uart_memory;
};

#endif //F0_UART_H
