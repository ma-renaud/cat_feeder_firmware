#include "f0_rcc.h"

uint32_t systick = 0;

void SysTick_Handler() {
  systick++;
}