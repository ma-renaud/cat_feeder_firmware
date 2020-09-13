#ifndef F0_BASIC_TIMER_MEMORY_H
#define F0_BASIC_TIMER_MEMORY_H

#include "f0_memory.h"

class F0BasicTimerMemory {
public:
  F0BasicTimerMemory() = default;
  ~F0BasicTimerMemory() = default;

protected:
  device_register CR1;
  device_register DIER;
  device_register SR;
  device_register EGR;
  device_register CNT;
  device_register PSC;
  device_register ARR;
};

#endif //F0_BASIC_TIMER_MEMORY_H
