#ifndef F0GPIOMEMORY_H
#define F0GPIOMEMORY_H

#include "IGpioMemory.h"

typedef uint32_t volatile device_register;

class F0GpioMemory : public IGpioMemory
{
   public:
      F0GpioMemory() = default;
      ~F0GpioMemory() = default;
      void toggle(Pins pin) override;

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
