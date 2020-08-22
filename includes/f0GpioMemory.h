#ifndef F0GPIOMEMORY_H
#define F0GPIOMEMORY_H

#include <cstdint>
#include "IGpio.h"

typedef uint32_t volatile device_register;

class F0GpioMemory {
public:
  F0GpioMemory() = default;
  ~F0GpioMemory() = default;
  GPIO_PinState readPin(GPIO_Pin pin);
  void write(GPIO_Pin pin, GPIO_PinState PinState);
  void toggle(GPIO_Pin pin);

protected:
  device_register MODER;
  device_register OTYPER;
  device_register OSPEEDR;
  device_register PUPDR;
  device_register IDR;
  device_register ODR;
  device_register BSRR;
  device_register LCKR;
  device_register AFR[2];
  device_register BRR;
};

#endif //F0GPIOMEMORY_H
