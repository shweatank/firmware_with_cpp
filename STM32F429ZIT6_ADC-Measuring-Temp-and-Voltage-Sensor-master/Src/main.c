/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "rcc.h"
#include "gpio.h"
#include "adc.h"
#include "uart.h"
#include <stdarg.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int channelSeq[] = {18, 13, 5, -1};
char uartPrintBuffer[512];
int count = 0;
int voltage_chn13, voltage_chn5, temp_chn18;

void uartPrint(char *message, ...) {
	va_list args;
	int length, i;

	va_start(args, message);

	length = vsnprintf(uartPrintBuffer, 0, message, args);

	if(length > 511)
		length = 511;
	vsnprintf(uartPrintBuffer, length + 1, message, args);

	for(i = 0; i < length; i++) {
		while(!(USART_IS_TX_REG_EMPTY(usart5)));
			usart5->DR = uartPrintBuffer[i];
	}
}



void enableAdc(AdcReg *adc) {

	if(adc == adc1)
		ENABLE_ADC1_CLK_GATING();

	else if(adc == adc2)
		ENABLE_ADC2_CLK_GATING();

	else if(adc == adc3)
		ENABLE_ADC3_CLK_GATING();

	else
		return;
	RESET_ADC();

	UNRESET_ADC();
	//ADC_START_CONVERSION(adc);
}

void readInternalTemp(AdcReg *adc) {

	  //sprintf(uartPrintBuffer, "Temperature: %.2f\n\n", temperature);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	ENABLE_USART5_CLK_GATING();
	ENABLE_GPIOA_CLK_GATING();
	ENABLE_GPIOC_CLK_GATING();
	RESET_GPIOA();
	RESET_USART5();
	RESET_GPIOC();
	UNRESET_GPIOA();
	UNRESET_GPIOC();
	UNRESET_USART5();
	enableAdc(adc1);

	adcChannelSamplingTime(adc1, 5, ADC_480_CYCLES);
	adcChannelSamplingTime(adc1, 13, ADC_480_CYCLES);
	ADC_SET_PRESCALER(ADC_PRESCALER_BY_2);
	adcChannelSamplingTime(adc1, 18, ADC_480_CYCLES);
	adcSetChannelSamplingSequence(adc1, channelSeq);
	adcConfigure(adc1, ADC_RESO_10_BIT | ADC_SCAN_MODE_ENABLE | ADC_RIGHT_ALIGNMENT | ADC_ON | ADC_EACH_CONV_EOC);
	gpioConfigurePin(gpioA, GpioPin5, GPIO_ANALOG | GPIO_PUSH_PULL | GPIO_VERY_HIGH_SPEED | GPIO_NO_PULL);
	gpioConfigurePin(gpioC, GpioPin3, GPIO_ANALOG | GPIO_PUSH_PULL | GPIO_VERY_HIGH_SPEED | GPIO_NO_PULL);
	gpioConfigurePin(gpioC, GpioPin12, GPIO_ALT_FUNC | GPIO_PUSH_PULL | GPIO_VERY_HIGH_SPEED | GPIO_NO_PULL);
	usartConfigure(usart5, USART_SAMPLING_16 | USART_RX_ENABLE | USART_TX_ENABLE | USART_PARITY_OFF | USART_WORDLENGTH_8 |  \
					  USART_STOP_BIT_1 | USART_ENABLE, 115200, 45000000);
	gpioConfigureAltFunc(gpioC, GpioPin12, GPIO_AF8);
	ADC_TEMP_SENSOR_ENABLE();
	//readInternalTemp(adc1);

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  ADC_CLEAR_ALL_FLAGS(adc1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  do {
		  do {
			  ADC_CLEAR_ALL_FLAGS(adc1);
			  ADC_START_CONVERSION(adc1);
			  while(!(ADC_HAS_CONVERSION_ENDED(adc1)))
				  if(ADC_IS_ADC_OVERRUN(adc1))
					  goto overrunOccured;
			  temp_chn18 = adcReadValue(adc1);
			  while(!(ADC_HAS_CONVERSION_ENDED(adc1)))
				  if(ADC_IS_ADC_OVERRUN(adc1))
					  goto overrunOccured;
			  voltage_chn13 = adcReadValue(adc1);
			  while(!(ADC_HAS_CONVERSION_ENDED(adc1)))
				  if(ADC_IS_ADC_OVERRUN(adc1))
					  goto overrunOccured;
			  voltage_chn5 = adcReadValue(adc1);


			  uartPrint("%d\t%d\t%d : %.3f\t%.3f\t     %.3f\n", temp_chn18, voltage_chn13, voltage_chn5, (((temp_chn18 * 0.00293551) - 0.76) / 0.0025) + 25, 3.0*voltage_chn13/1023,  3.0*voltage_chn5/1023);
			  HAL_Delay(100);
		  } while(1);
		  overrunOccured:
		  ADC_CLEAR_STATUS(adc1, ADC_OVR | ADC_EOC);
  }while(1);



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
