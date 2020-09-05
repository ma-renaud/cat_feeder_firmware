#ifndef F0_UART_MEMORY_H
#define F0_UART_MEMORY_H

#include <cstdint>
#include <string>
#include "i_uart.h"
#include "f0_memory.h"

#include "circular_buffer.h"

class F0UartMemory {
public:
  F0UartMemory() = default;
  ~F0UartMemory() = default;
  void init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate, uint32_t SystemCoreClock);
  void enable_interrupts();

  void send_char(char data);
  void send_string(const std::string& string);
  void clear_debug_screen();

protected:
  device_register CR1;
  device_register CR2;
  device_register CR3;
  device_register BRR;
  device_register RESERVED;
  device_register RTOR;
  device_register RQR;
  device_register ISR;
  device_register ICR;
  device_register RDR;
  device_register TDR;

private:
  void set_parity(Uart_Parity parity);
  void set_stop_bit(Uart_Stop_Bit stop_bit);
  void set_baudrate(Uart_Baudrate baudrate, uint32_t SystemCoreClock);
  void enable_uart();
};

#endif //F0_UART_MEMORY_H
