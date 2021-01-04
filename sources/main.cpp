/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

#include "i_gpio.h"
#include "f0_gpio.h"
#include "i_uart.h"
#include "f0_uart.h"
#include "f0_rcc.h"
#include "f0_basic_timer.h"
#include "isr_vectors.h"

#include <memory>

#define ever ;;

std::unique_ptr<IRcc> rcc;
std::unique_ptr<IGpio> led2;
std::unique_ptr<IGpio> uart2_tx;
std::unique_ptr<IGpio> uart2_rx;
std::unique_ptr<IUart> uart2;
std::unique_ptr<F0BasicTimer> timer6;

void init_periph();
void tim6_callback();

int main() {
  /* Configure peripherals */
  __set_PRIMASK(1);
  init_periph();
  __set_PRIMASK(0);
  /* Configure peripherals end*/

  led2->write(Gpio_PinState::SET);
  uart2->clear_screen();

  for (ever) {
  }

} /*--------------------------------------------------------------------------*/

void tim6_callback(){
  led2->toggle();
  //relay->toggle();
}

void HardFault_Handler() {
  for (ever) {
    asm("BKPT #0");
  }
}

void init_periph() {
  rcc = std::make_unique<F0Rcc>(reinterpret_cast<uintptr_t>(RCC));
  rcc->init(Rcc_PLL_Source::HSI, Rcc_PLL_Mul::MUL12);

  led2 = std::make_unique<F0Gpio>(Gpio_Port::PORTA, Gpio_Pin::PIN_5, rcc.get());
  led2->init(Gpio_Mode::DIGITAL_OUT);

  uart2_tx = std::make_unique<F0Gpio>(Gpio_Port::PORTA, Gpio_Pin::PIN_2, rcc.get());
  uart2_tx->init(Gpio_Mode::ALTERNATE_FUNCTION, Gpio_Alt_Func::AF1, Gpio_Alt_Func_Mode::TX);
  uart2_rx = std::make_unique<F0Gpio>(Gpio_Port::PORTA, Gpio_Pin::PIN_3, rcc.get());
  uart2_rx->init(Gpio_Mode::ALTERNATE_FUNCTION, Gpio_Alt_Func::AF1, Gpio_Alt_Func_Mode::RX);
  uart2 = std::make_unique<F0Uart>(reinterpret_cast<uintptr_t>(USART2), rcc.get());
  uart2->init(Uart_Parity::NONE, Uart_Stop_Bit::ONE_BIT, Uart_Baudrate::BAUD_9600, Uart_Mode::INTERRUPT);
  registerHandler(USART2_IRQn, [u2 = uart2.get()]() { reinterpret_cast<F0Uart *>(u2)->IRQHandler(); });

  timer6 = std::make_unique<F0BasicTimer>(reinterpret_cast<uintptr_t>(TIM6), rcc.get());
  timer6->init(12973, 3700, 0);
  timer6->register_callback([]() { tim6_callback(); });
  registerHandler(TIM6_IRQn, [tim6 = timer6.get()]() { reinterpret_cast<F0BasicTimer *>(tim6)->IRQHandler(); });
}

//void MX_TIM14_Init() {
//  htim14.Instance = TIM14;
//  htim14.Init.Prescaler = 23999;
//  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim14.Init.Period = 1999;
//  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  HAL_TIM_Base_Init(&htim14);
//} /*--------------------------------------------------------------------------*/
//
//void MX_TIM16_Init() {
//
//  TIM_OC_InitTypeDef sConfigOC;
//
//  htim16.Instance = TIM16;
//  htim16.Init.Prescaler = 4999;
//  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim16.Init.Period = 191;
//  HAL_TIM_PWM_Init(&htim16);
//
//  sConfigOC.OCMode = TIM_OCMODE_PWM1;
//  sConfigOC.Pulse = 0;
//  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
//  HAL_TIM_PWM_ConfigChannel(&htim16, &sConfigOC, TIM_CHANNEL_1);
//} /*--------------------------------------------------------------------------*/
