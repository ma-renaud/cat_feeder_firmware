#include "f0_basic_timer.h"

F0BasicTimer::F0BasicTimer(uintptr_t timer_addr, IRcc *rcc) {
  timer_memory = reinterpret_cast<F0TimerMemory *>(timer_addr);
  Rcc_Timer timer = get_timer_rcc();
  rcc->enable_timer(timer);
}

Rcc_Timer F0BasicTimer::get_timer_rcc() {
  Rcc_Timer timer = Rcc_Timer::NONE;

  if (timer_memory == reinterpret_cast<F0TimerMemory *>(Timer_Peripheral::TIMER6))
    timer = Rcc_Timer::TIMER6;
  else if (timer_memory == reinterpret_cast<F0TimerMemory *>(Timer_Peripheral::TIMER7))
    timer = Rcc_Timer::TIMER7;

  return timer;
}

void F0BasicTimer::enable_interrupts(uint32_t priority) {
  timer_memory->enable_interrupts();

  IRQn_Type irqn = HardFault_IRQn;
  if (timer_memory == reinterpret_cast<F0TimerMemory *>(Timer_Peripheral::TIMER6))
    irqn = static_cast<IRQn_Type>(Timer_IRQn::TIM6_IRQn);
  else if (timer_memory == reinterpret_cast<F0TimerMemory *>(Timer_Peripheral::TIMER7))
    irqn = static_cast<IRQn_Type>(Timer_IRQn::TIM7_IRQn);

  if (irqn != HardFault_IRQn) {
    NVIC_EnableIRQ(irqn);
    NVIC_SetPriority(irqn, priority);
  }
}

void F0BasicTimer::IRQHandler() {
  timer_memory->clear_interrupt_flag();
  if (callback)
    callback();
}
