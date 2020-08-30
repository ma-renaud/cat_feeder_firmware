#ifndef IUART_H
#define IUART_H

#include <cstdint>
#include <string>

enum class Uart_Peripheral : uint8_t
{
  UART1 = 0,
  UART2
};

enum class Uart_Mode : uint8_t
{
  POOLING = 0,
  INTERRUPT,
  DMA
};

enum class Uart_Parity : uint8_t
{
  NONE = 0,
  EVEN,
  ODD
};

enum class Uart_Stop_Bit : uint8_t
{
  ONE_BIT = 0,
  TWO_BITS,
  ONE_AND_HALF_BITS
};

enum class Uart_Baudrate : uint32_t
{
  BAUD_9600 = 9600,
  BAUD_19200 = 19200,
  BAUD_57600 = 57600,
  BAUD_115200 = 115200
};

class IUart
{
public:
  virtual void send_char(char data) = 0;
  virtual void send_string(std::string string) = 0;
  virtual void clear_debug_screen() = 0;
  virtual void init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate) = 0;
  virtual void enable_interrupts(uint32_t priority) = 0;
};

#endif //IUART_H
