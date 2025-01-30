#include "main.h"
#include "cmsis_os2.h"
#include "stm32f4xx_hal.h"

/* Semaphore handle */
osSemaphoreId_t ledSemaphore;
osThreadId_t ledBlinkTaskHandle;

/* Function prototypes */
void SystemClock_Config(void);
void StartLedBlinkTask(void *argument);

int main(void)
{
    /* HAL Initialization */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Create the semaphore */
    osSemaphoreAttr_t semaphore_attributes = {
        .name = "LED_Semaphore"
    };
    ledSemaphore = osSemaphoreNew(1, 1, &semaphore_attributes);

    /* Create the thread for LED blinking */
    osThreadAttr_t ledBlinkTask_attributes = {
        .name = "LedBlinkTask",
        .stack_size = 128 * 4,
        .priority = osPriorityNormal
    };
    ledBlinkTaskHandle = osThreadNew(StartLedBlinkTask, NULL, &ledBlinkTask_attributes);

    /* Start FreeRTOS scheduler */
    osKernelStart();

    /* We should never get here */
    while (1)
    {
    }
}

void StartLedBlinkTask(void *argument)
{
    /* Initialize the LED pin */
    __HAL_RCC_GPIOG_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    while (1)
    {
        /* Wait for the semaphore */
        osSemaphoreAcquire(ledSemaphore, osWaitForever);

        /* Toggle the LED */
        HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);

        /* Delay */
        osDelay(500);  // 500ms delay

        /* Release the semaphore */
        osSemaphoreRelease(ledSemaphore);
    }
}

void SystemClock_Config(void)
{
    /* Configure the system clock to 180 MHz using HSE and PLL */
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* Configure the main internal regulator output voltage */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* Initializes the RCC Oscillators */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;  // 180 MHz
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /* Initializes the CPU, AHB, and APB busses clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

    /* Update the SystemCoreClock global variable */
    SystemCoreClockUpdate();
}

void HAL_MspInit(void)
{
    /* This function is used to initialize the MSP */
    /* No specific hardware initialization needed here for now */
}

void Error_Handler(void)
{
    /* This function is executed in case of an error */
    while (1)
    {
    }
}
