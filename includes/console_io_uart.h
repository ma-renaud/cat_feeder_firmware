#ifndef CONSOLEIOUART_H
#define CONSOLEIOUART_H

#include "console_io.h"
#include "i_uart.h"

class ConsoleIoUart : public Console_io {
public:
  explicit ConsoleIoUart(IUart *uart) : uart(uart) {}
  ~ConsoleIoUart() override = default;

  int print(const char* out) override {
    return uart->send_string(out);
  }

  int get_char() override {
    uint8_t data;
    if (uart->get_byte(data))
      return data;
    else
      return EOF;
  }

private:
  IUart *uart;
};

#endif //CONSOLEIOUART_H
