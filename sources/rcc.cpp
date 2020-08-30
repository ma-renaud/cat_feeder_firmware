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

void enable_uart1_clock() {
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Activate Uart clock
  RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST; // Place uart 1 in reset mode
  RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST; // Remove Uart 1 from reset mode

}

void enable_uart2_clock() {
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Clock activation for Uart2
  RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST; // Set Uart2 in reset state
  RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST; // Remove uart2 state from reset
}

#ifdef __cplusplus
extern "C" {
#endif

void SysTick_Handler(void) {
  systick++;
}

#ifdef __cplusplus
}
#endif