#ifndef F0_RCC_H
#define F0_RCC_H

#include "stm32f0xx.h"
#include "i_rcc.h"
#include "f0_rcc_memory.h"

class F0Rcc : public IRcc {
public:
  F0Rcc(uintptr_t rcc_addr) {
    rcc_memory = reinterpret_cast<F0RccMemory *>(rcc_addr);
  }
  ~F0Rcc() = default;

  void init(Rcc_PLL_Source pll_src, Rcc_PLL_Mul pll_mul) override {
    rcc_memory->init(pll_src, pll_mul);

    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / Milliseconds);
  }

  void enable_gpio_port(Rcc_Gpio port) override {
    rcc_memory->enable_gpio_port(port);
  }

  void enable_and_reset_uart(Rcc_Uart uart) override {
    rcc_memory->enable_and_reset_uart(uart);
  }

private:
  F0RccMemory *rcc_memory;
  static constexpr uint32_t Milliseconds = 1000;
};

#endif //F0_RCC_H
