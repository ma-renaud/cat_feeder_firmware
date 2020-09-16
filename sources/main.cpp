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
#include "console.h"
#include "console_io_uart.h"
#include "console_cmd_table.h"

#define ever ;;

std::unique_ptr<F0BasicTimer> timer6;

int main() {
  /* Configure peripherals */
  __set_PRIMASK(1);

  std::unique_ptr<IRcc> rcc = std::make_unique<F0Rcc>(reinterpret_cast<uintptr_t>(RCC));
  rcc->init(Rcc_PLL_Source::HSI, Rcc_PLL_Mul::MUL12);

  std::unique_ptr<IGpio> led2 = std::make_unique<F0Gpio>(Gpio_Port::PORTA, Gpio_Pin::PIN_5, rcc.get());
  led2->init(Gpio_Mode::DIGITAL_OUT);

  std::unique_ptr<IGpio> uart2_tx = std::make_unique<F0Gpio>(Gpio_Port::PORTA, Gpio_Pin::PIN_2, rcc.get());
  uart2_tx->init(Gpio_Mode::ALTERNATE_FUNCTION, Gpio_Alt_Func::AF1, Gpio_Alt_Func_Mode::TX);
  std::unique_ptr<IGpio> uart2_rx = std::make_unique<F0Gpio>(Gpio_Port::PORTA, Gpio_Pin::PIN_3, rcc.get());
  uart2_rx->init(Gpio_Mode::ALTERNATE_FUNCTION, Gpio_Alt_Func::AF1, Gpio_Alt_Func_Mode::RX);
  std::unique_ptr<IUart> uart2 = std::make_unique<F0Uart>(reinterpret_cast<uintptr_t>(USART2), rcc.get());
  uart2->init(Uart_Parity::NONE, Uart_Stop_Bit::ONE_BIT, Uart_Baudrate::BAUD_9600, Uart_Mode::INTERRUPT);
  registerHandler(USART2_IRQn, [u2 = uart2.get()]() { reinterpret_cast<F0Uart *>(u2)->IRQHandler(); });

  timer6 = std::make_unique<F0BasicTimer>(reinterpret_cast<uintptr_t>(TIM6), rcc.get());
  timer6->init(1000, 3700, 0);

  __set_PRIMASK(0);
  /* Configure peripherals end*/

  led2->write(Gpio_PinState::SET);
  uart2->clear_screen();

  ConsoleIoUart console_io(uart2.get());

  Data<64, 64> cli_data;
  Console cli(console_io, cli_data.get_buffer(), cli_data.get_root_table(), true, ">", "\r\n");
  cli.add_cmd_table("Base table", app_cmd::get_app_table());
  cli.start("");

  uint32_t counter_led = 0;
  for (ever) {
    counter_led++;
    if (counter_led >= 5000u) {
      led2->toggle();
      counter_led = 0;
    }
    cli.process();
  }

} /*--------------------------------------------------------------------------*/

void HardFault_Handler() {
  for (ever) {
  }
}

//void MX_TIM6_Init() {
//  htim6.Instance = TIM6;
//  htim6.Init.Prescaler = 3699;
//  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim6.Init.Period = 999;
//  htim6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  HAL_TIM_Base_Init(&htim6);
//} /*--------------------------------------------------------------------------*/
//
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
