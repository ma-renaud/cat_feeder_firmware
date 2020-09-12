#ifndef I_UART_H
#define I_UART_H

#include <cstdint>
#include <string>

enum class Uart_Peripheral : uint32_t
{
  UART1 = 0x40013800,
  UART2 = 0x40004400
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
  virtual void clear_screen() = 0;
  virtual void init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate, Uart_Mode mode) = 0;
  virtual void init(Uart_Parity parity, Uart_Stop_Bit stop_bit, Uart_Baudrate baudrate, Uart_Mode mode, uint32_t priority) = 0;
};

#endif //I_UART_H
