#ifndef F0_UART_MEMORY_H
#define F0_UART_MEMORY_H

#include <cstdint>
#include <string>
#include "i_uart.h"

#include "circular_buffer.h"

class F0UartMemory {
public:
  F0UartMemory() = default;
  ~F0UartMemory() = default;
  void init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate);
  void enable_interrupts(uint32_t priority);

  void send_char(char data);
  void send_string(std::string string);
  void clear_debug_screen();

protected:
  uint32_t CR1;
  uint32_t CR2;
  uint32_t CR3;
  uint32_t BRR;
  uint32_t RESERVED;
  uint32_t RTOR;
  uint32_t RQR;
  uint32_t ISR;
  uint32_t ICR;
  uint32_t RDR;
  uint32_t TDR;

private:
  void set_parity(Uart_Parity parity);
  void set_stop_bit(Uart_Stop_Bit stop_bit);
  void set_baudrate(Uart_Baudrate baudrate);
};

#endif //F0_UART_MEMORY_H
