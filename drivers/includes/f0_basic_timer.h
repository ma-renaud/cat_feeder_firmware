#ifndef CAT_FEEDER__F0_BASIC_TIMER_H
#define CAT_FEEDER__F0_BASIC_TIMER_H

#include <functional>
#include <cstdint>
#include "f0_basic_timer_memory.h"
#include "i_timer.h"
#include "i_rcc.h"
#include "stm32f0xx.h"

class F0BasicTimer : public ITimer {
public:
  explicit F0BasicTimer(uintptr_t timer_addr, IRcc *rcc);
  ~F0BasicTimer() = default;

  void init(uint16_t period, uint16_t prescaler, uint32_t priority) override {
    timer_memory->init(period, prescaler);
    enable_interrupts(priority);
  }

private:
  F0BasicTimerMemory *timer_memory;
  Rcc_Timer get_timer_rcc();

  void enable_interrupts(uint32_t priority);
};

#endif //CAT_FEEDER__F0_BASIC_TIMER_H
