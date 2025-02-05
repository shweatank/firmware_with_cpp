/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private variables ---------------------------------------------------------*/
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osTimerId_t myTimer01Handle;
const osTimerAttr_t myTimer01_attributes = { .name = "myTimer01" };

osTimerId_t myTimer02Handle;
const osTimerAttr_t myTimer02_attributes = { .name = "myTimer02" };

/* Function Prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartDefaultTask(void *argument);
void Callback01(void *argument);
void Callback02(void *argument);

/* Main Function */
int main(void)
{
  /* Initialize the hardware */
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  /* Initialize FreeRTOS kernel */
  osKernelInitialize();

  /* Create FreeRTOS timers */
  myTimer01Handle = osTimerNew(Callback01, osTimerPeriodic, NULL, &myTimer01_attributes);
  myTimer02Handle = osTimerNew(Callback02, osTimerPeriodic, NULL, &myTimer02_attributes);

  /* Start the timers */
  if (myTimer01Handle != NULL)
  {
    osTimerStart(myTimer01Handle, 5000);  // Blink LED1 (PG13) every 500ms
  }

  if (myTimer02Handle != NULL)
  {
    osTimerStart(myTimer02Handle, 1000); // Blink LED2 (PG14) every 1000ms
  }

  /* Create default thread */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* Start the scheduler */
  osKernelStart();

  while (1) {} // Should never reach here
}

/* GPIO Initialization */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Enable GPIO ports */
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /* Configure PG13 and PG14 as output */
  GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* Ensure LEDs are off initially */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13 | GPIO_PIN_14, GPIO_PIN_RESET);
}

/* FreeRTOS Timer Callback for LED1 */
void Callback01(void *argument)
{
  HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);  // Toggle LED1 (PG13)
}

/* FreeRTOS Timer Callback for LED2 */
void Callback02(void *argument)
{
  HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);  // Toggle LED2 (PG14)
}

/* Default Task */
void StartDefaultTask(void *argument)
{
  for (;;)
  {
    osDelay(1);
  }
}

/* System Clock Configuration */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* Error Handler */
void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  /* Custom assert error message can be added here */
}
#endif
