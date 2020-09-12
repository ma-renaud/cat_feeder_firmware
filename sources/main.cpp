/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
//#include "stm32f0xx_hal.h"

#include "../drivers/includes/i_gpio.h"
#include "../drivers/includes/f0_gpio.h"

#include "../drivers/includes/i_uart.h"
#include "../drivers/includes/f0_uart.h"

#include "../drivers/includes/i_rcc.h"
#include "../drivers/includes/f0_rcc.h"

#include "isr_vectors.h"

#include <memory>
//#include <string>
//#include "console.h"
#include "circular_buffer.h"

int main() {
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  //HAL_Init();

  /* Configure the system clock */
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

  __set_PRIMASK(0);

  led2->write(Gpio_PinState::SET);
  uart2->clear_screen();

//  Console cli(io, cli_buffer, cli_root_table, true, ">", "\r\n");

  uint32_t counter = 0;
  while (true) {
    counter++;
    if (counter >= 2000000u) {
      led2->toggle();
      uart2->send_char('a');
      counter = 0;
    }
  }

} /*--------------------------------------------------------------------------*/

void HardFault_Handler() {
  while (1) {
  }
}


//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//  std::string msg = "boom\r\n";
//  if (htim->Instance == TIM14) {
//    HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
//    HAL_UART_Transmit(huart, reinterpret_cast<uint8_t *>(&msg[0]), static_cast<uint16_t>(msg.length()), HAL_MAX_DELAY);
//  }
//
//  if (htim->Instance == TIM6)
//    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin));
//} /*--------------------------------------------------------------------------*/

/** System Clock Configuration
*/


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
//
//  * @brief USART1 Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_USART1_UART_Init() {
//
//  /* USER CODE BEGIN USART1_Init 0 */
//
//  /* USER CODE END USART1_Init 0 */
//
//  /* USER CODE BEGIN USART1_Init 1 */
//
//  /* USER CODE END USART1_Init 1 */
//  huart_bluetooth.Instance = USART1;
//  huart_bluetooth.Init.BaudRate = 9600;
//  huart_bluetooth.Init.WordLength = UART_WORDLENGTH_8B;
//  huart_bluetooth.Init.StopBits = UART_STOPBITS_1;
//  huart_bluetooth.Init.Parity = UART_PARITY_NONE;
//  huart_bluetooth.Init.Mode = UART_MODE_TX_RX;
//  huart_bluetooth.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart_bluetooth.Init.OverSampling = UART_OVERSAMPLING_16;
//
//  if (HAL_UART_Init(&huart_bluetooth) != HAL_OK) {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN USART1_Init 2 */
//
//  /* USER CODE END USART1_Init 2 */
//
//} /*--------------------------------------------------------------------------*/
//
///**
//  * @brief USART2 Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_USART2_UART_Init() {
//
//  /* USER CODE BEGIN USART2_Init 0 */
//
//  /* USER CODE END USART2_Init 0 */
//
//  /* USER CODE BEGIN USART2_Init 1 */
//
//  /* USER CODE END USART2_Init 1 */
//  huart_usb.Instance = USART2;
//  huart_usb.Init.BaudRate = 9600;
//  huart_usb.Init.WordLength = UART_WORDLENGTH_8B;
//  huart_usb.Init.StopBits = UART_STOPBITS_1;
//  huart_usb.Init.Parity = UART_PARITY_NONE;
//  huart_usb.Init.Mode = UART_MODE_TX_RX;
//  huart_usb.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart_usb.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart_usb) != HAL_OK) {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN USART2_Init 2 */
//
//  /* USER CODE END USART2_Init 2 */
//
//} /*--------------------------------------------------------------------------*/
//
///**
//  * @brief  This function is executed in case of error occurrence.
//  * @param  None
//  * @retval None
//  */
//static void Error_Handler() {
//  __asm__("BKPT");
//  while (true) {}
//}
//
//#ifdef USE_FULL_ASSERT
//
///**
//   * @brief Reports the name of the source file and the source line number
//   * where the assert_param error has occurred.
//   * @param file: pointer to the source file name
//   * @param line: assert_param error line source number
//   * @retval None
//   */
//void assert_failed(uint8_t* file, uint32_t line)
//{
//  /* USER CODE BEGIN 6 */
//  /* User can add his own implementation to report the file name and line number,
//    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//  /* USER CODE END 6 */
//
//}
//
//#endif
