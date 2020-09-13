#ifndef F0_UART_H
#define F0_UART_H

#include <string>
#include "i_uart.h"
#include "i_rcc.h"
#include "f0_uart_memory.h"
#include "stm32f0xx.h"
#include "circular_buffer.h"

class F0Uart : public IUart {
public:
  explicit F0Uart(uintptr_t uart_addr, IRcc *rcc);
  ~F0Uart() = default;

  void init(Uart_Parity parity,
            Uart_Stop_Bit stop_bit,
            Uart_Baudrate baudrate,
            Uart_Mode mode,
            uint32_t priority) override;
  void init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate, Uart_Mode mode) override {
    init(parity, stop_bit, baudrate, mode, 0);
  }
  bool send_byte(uint8_t data) override;
  std::size_t send_string(std::string string) override;
  bool get_byte(uint8_t &data) override;
  void clear_screen() override;

  void IRQHandler();

private:
  F0UartMemory *uart_memory;
  uint32_t system_core_clock;
  CircularBuffer<uint8_t, 32> buf_tx;
  CircularBuffer<uint8_t, 32> buf_rx;
  void enable_interrupts(uint32_t priority);
};

#endif //F0_UART_H
