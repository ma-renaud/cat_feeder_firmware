#ifndef F0_BASIC_TIMER_MEMORY_H
#define F0_BASIC_TIMER_MEMORY_H

#include "f0_memory.h"
#include "f0_timer_memory.h"

class F0BasicTimerMemory {
public:
  F0BasicTimerMemory() = default;
  ~F0BasicTimerMemory() = default;
  void init(uint16_t period, uint16_t prescaler);
  void enable_interrupts();

  void clear_interrupt_flag();

protected:
  device_register CR1;
  device_register RESERVED;
  device_register RESERVED_2;
  device_register DIER;
  device_register SR;
  device_register EGR;
  device_register RESERVED_3;
  device_register RESERVED_4;
  device_register RESERVED_5;
  device_register CNT;
  device_register PSC;
  device_register ARR;
};

#endif //F0_BASIC_TIMER_MEMORY_H
