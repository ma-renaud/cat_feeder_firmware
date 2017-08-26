/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "diag/Trace.h"

TIM_HandleTypeDef htim14;
TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config();
static void Error_Handler();
static void MX_GPIO_Init();
static void MX_TIM14_Init();
static void MX_TIM16_Init();
static void MX_TIM17_Init();

int main()
{
   /* MCU Configuration----------------------------------------------------------*/

   /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
   HAL_Init();

   /* Configure the system clock */
   SystemClock_Config();

   /* Initialize all configured peripherals */
   MX_GPIO_Init();
   MX_TIM14_Init();
   MX_TIM16_Init();
   MX_TIM17_Init();

   if (HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1) != HAL_OK) {
      Error_Handler();
   }

   if (HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1) != HAL_OK) {
      Error_Handler();
   }

   htim16.Instance->CCR1 = 25;
   htim17.Instance->CCR1 = 25;

#ifdef DEBUG
   trace_printf("System clock: %u Hz\n", SystemCoreClock);
#endif

   while (1) { }

} /*--------------------------------------------------------------------------*/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
   if (htim->Instance == TIM14)
      HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
} /*--------------------------------------------------------------------------*/

/** System Clock Configuration
*/
void SystemClock_Config()
{
   RCC_OscInitTypeDef RCC_OscInitStruct;
   RCC_ClkInitTypeDef RCC_ClkInitStruct;
   RCC_PeriphCLKInitTypeDef PeriphClkInit;

   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14 | RCC_OSCILLATORTYPE_HSI48;
   RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
   RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
   RCC_OscInitStruct.HSI14CalibrationValue = 16;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
   HAL_RCC_OscConfig(&RCC_OscInitStruct);

   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                 | RCC_CLOCKTYPE_PCLK1;
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
   HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

   PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
   PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
   HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

   HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

   HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

   /* SysTick_IRQn interrupt configuration */
   HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
} /*--------------------------------------------------------------------------*/

void MX_TIM14_Init()
{
   htim14.Instance = TIM14;
   htim14.Init.Prescaler = 23999;
   htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim14.Init.Period = 1999;
   htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
   HAL_TIM_Base_Init(&htim14);

   HAL_TIM_Base_Start_IT(&htim14); // start timer interrupts
   HAL_NVIC_SetPriority(TIM14_IRQn, 0, 1);
   HAL_NVIC_EnableIRQ(TIM14_IRQn);
} /*--------------------------------------------------------------------------*/

void MX_TIM16_Init()
{

   TIM_OC_InitTypeDef sConfigOC;

   htim16.Instance = TIM16;
   htim16.Init.Prescaler = 19;
   htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim16.Init.Period = 99;
   HAL_TIM_PWM_Init(&htim16);


   sConfigOC.OCMode = TIM_OCMODE_PWM1;
   sConfigOC.Pulse = 50;
   sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
   sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
   sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
   HAL_TIM_PWM_ConfigChannel(&htim16, &sConfigOC, TIM_CHANNEL_1);
}

void MX_TIM17_Init()
{

   TIM_OC_InitTypeDef sConfigOC;

   htim17.Instance = TIM17;
   htim17.Init.Prescaler = 19;
   htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim17.Init.Period = 99;
   HAL_TIM_PWM_Init(&htim17);

   sConfigOC.OCMode = TIM_OCMODE_PWM1;
   sConfigOC.Pulse = 50;
   sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
   sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
   sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
   HAL_TIM_PWM_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1);
}

void MX_GPIO_Init()
{
   GPIO_InitTypeDef GPIO_InitStruct;

   /* GPIO Ports Clock Enable */
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();

   /*Configure GPIO pin : LD3_Pin */
   GPIO_InitStruct.Pin = LD3_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(LD3_GPIO_Port, &GPIO_InitStruct);

   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
} /*--------------------------------------------------------------------------*/

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler()
{
   __asm__("BKPT");
   while (1) { }
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif
