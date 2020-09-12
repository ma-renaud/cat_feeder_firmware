#ifndef I_RCC_H
#define I_RCC_H

#include <cstdint>

enum class Rcc_SysClock_Source : uint8_t {
  HSI = 0,
  HSE,
  PLL
};

enum class Rcc_PLL_Source : uint32_t {
  HSI = 0,
  HSE = 0x00010000U
};

enum class Rcc_PLL_Mul : uint32_t {
  MUL2 = 0x00000000U,
  MUL3 = 0x00040000U,
  MUL4 = 0x00080000U,
  MUL5 = 0x000C0000U,
  MUL6 = 0x00100000U,
  MUL7 = 0x00140000U,
  MUL8 = 0x00180000U,
  MUL9 = 0x001C0000U,
  MUL10 = 0x00200000U,
  MUL11 = 0x00240000U,
  MUL12 = 0x00280000U,
  MUL13 = 0x002C0000U,
  MUL14 = 0x00300000U,
  MUL15 = 0x00340000U,
  MUL16 = 0x00380000U
};

enum class Rcc_Gpio : uint32_t {
  PORTA = 0x00020000U,
  PORTB = 0x00040000U,
  PORTC = 0x00080000U,
  PORTD = 0x00100000U,
  PORTF = 0x00400000U
};

enum class Rcc_Uart : uint32_t {
  NONE = 0,
  UART1 = 0x00004000U,
  UART2 = 0x00020000U
};

class IRcc {
public:
  virtual void init(Rcc_PLL_Source pll_src, Rcc_PLL_Mul pll_mul) = 0;
  virtual void enable_gpio_port(Rcc_Gpio port) = 0;
  virtual void enable_and_reset_uart(Rcc_Uart uart) = 0;
  virtual uint32_t get_system_core_clock() = 0;
  virtual uint32_t get_systick() = 0;
};

#endif //I_RCC_H
