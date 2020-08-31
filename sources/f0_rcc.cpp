#include "f0_rcc.h"

uint32_t systick = 0;

#ifdef __cplusplus
extern "C" {
#endif

void SysTick_Handler(void) {
  systick++;
}

#ifdef __cplusplus
}
#endif