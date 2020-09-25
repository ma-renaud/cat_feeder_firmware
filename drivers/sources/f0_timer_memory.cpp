#include "f0_timer_memory.h"

void F0TimerMemory::init(uint16_t period, uint16_t prescaler) {
  ARR = period - 1;
  PSC = prescaler - 1;
  CR1 |= to_underlying(CR1::CEN);
  EGR |= to_underlying(EGR::UG);
}

void F0TimerMemory::enable_interrupts() {
  DIER = to_underlying(DIER::UIE);
}

void F0TimerMemory::clear_interrupt_flag() {
  SR = ~(to_underlying(SR::UIF));
}