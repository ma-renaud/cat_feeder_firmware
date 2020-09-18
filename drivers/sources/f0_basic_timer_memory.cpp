#include "f0_basic_timer_memory.h"

void F0BasicTimerMemory::init(uint16_t period, uint16_t prescaler) {
  ARR = period - 1;
  PSC = prescaler - 1;
  CR1 |= to_underlying(CR1::CEN);
  EGR |= to_underlying(EGR::UG);
}

void F0BasicTimerMemory::enable_interrupts() {
  DIER = to_underlying(DIER::UIE);
}

void F0BasicTimerMemory::clear_interrupt_flag() {
  SR = ~(to_underlying(SR::UIF));
}