#ifndef F0RCCMEMORY_H
#define F0RCCMEMORY_H

#include "f0_memory.h"
#include "i_rcc.h"

class F0RccMemory {
public:
  F0RccMemory() = default;
  ~F0RccMemory() = default;

  void init(Rcc_PLL_Source pll_src, Rcc_PLL_Mul pll_mul);
  void enable_gpio_port(Rcc_Gpio port);
  void enable_and_reset_uart(Rcc_Uart uart);

protected:
  device_register CR;
  device_register CFGR;
  device_register CIR;
  device_register APB2RSTR;
  device_register APB1RSTR;
  device_register AHBENR;
  device_register APB2ENR;
  device_register APB1ENR;
  device_register BDCR;
  device_register CSR;
  device_register AHBRSTR;
  device_register CFGR2;
  device_register CFGR3;
  device_register CR2;
};

#endif //F0RCCMEMORY_H
