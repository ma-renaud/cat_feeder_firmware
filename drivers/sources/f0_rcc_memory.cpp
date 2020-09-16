#include "../includes/f0_rcc_memory.h"

enum class Rcc_Clock_Status: uint32_t {
  HSIRDY = 0x00000002U,
  HSERDY = 0x00020000U,
  PLLRDY = 0x02000000U
};

enum class Rcc_Source_Enable: uint32_t {
  HSION = 0x00000001U,
  HSEON = 0x00010000U,
  PLLON = 0x01000000U
};

void F0RccMemory::init(Rcc_PLL_Source pll_src, Rcc_PLL_Mul pll_mul) {
  if (pll_src == Rcc_PLL_Source::HSI) {
    CR |= static_cast<uint32_t>(Rcc_Source_Enable::HSION);
  }

  CFGR |= (static_cast<uint32_t>(pll_mul) | static_cast<uint32_t>(Rcc_SysClock_Source::PLL));
  CR |= static_cast<uint32_t>(Rcc_Source_Enable::PLLON);

  while (!(CR & static_cast<uint32_t>(Rcc_Clock_Status::PLLRDY)));
}

void F0RccMemory::enable_gpio_port(Rcc_Gpio port) {
  AHBENR |= static_cast<uint32_t>(port);
}

void F0RccMemory::enable_and_reset_uart(Rcc_Uart uart) {
  APB1ENR |= static_cast<uint32_t>(uart); // Clock activation for Uart
  APB1RSTR |= static_cast<uint32_t>(uart); // Set Uart in reset state
  APB1RSTR &= ~(static_cast<uint32_t>(uart)); // Remove uart state from reset
}

void F0RccMemory::enable_timer(Rcc_Timer timer) {
  APB1ENR |= to_underlying(timer);
}
