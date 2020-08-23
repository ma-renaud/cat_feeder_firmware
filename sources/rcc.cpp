#include "rcc.h"
#include "stm32f0xx.h"

#define Milliseconds ((uint32_t) 1000)
uint32_t systick = 0;

void SystemClock_Config() {
  // RCC configuration
  RCC->CR = RCC_CR_HSION;
  RCC->CFGR = RCC_CFGR_PLLMUL12 | RCC_CFGR_SW_PLL;
  RCC->CR |= RCC_CR_PLLON;

  while (!(RCC->CR & RCC_CR_PLLRDY)); // Wait for the PPL to be ready

  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / Milliseconds);
}

#ifdef __cplusplus
extern "C" {
#endif

void SysTick_Handler(void)
{
  systick++;
}

#ifdef __cplusplus
}
#endif