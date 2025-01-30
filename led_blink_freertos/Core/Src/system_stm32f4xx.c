#include "main.h"
#include "cmsis_os.h"

// Semaphore handle
osSemaphoreId_t myBinarySem01Handle;

// Message Queues
osMessageQueueId_t led_onHandle;
osMessageQueueId_t led_offHandle;

// Event Flags
osEventFlagsId_t eventoled_onHandle;
osEventFlagsId_t start_eventHandle;

// Task handles
osThreadId_t Task1_LED_onHandle;
osThreadId_t Task_Led_offHandle;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartDefaultTask(void *argument);
void StartTask02(void *argument);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
  
    osKernelInitialize();  // Initialize RTOS Kernel
  
    // Create Semaphore
    myBinarySem01Handle = osSemaphoreNew(1, 1, NULL);
  
    // Create Message Queues
    led_onHandle = osMessageQueueNew(16, sizeof(uint16_t), NULL);
    led_offHandle = osMessageQueueNew(16, sizeof(uint16_t), NULL);
  
    // Create Event Flags
    eventoled_onHandle = osEventFlagsNew(NULL);
    start_eventHandle = osEventFlagsNew(NULL);
  
    // Create Tasks
    Task1_LED_onHandle = osThreadNew(StartDefaultTask, NULL, NULL);
    Task_Led_offHandle = osThreadNew(StartTask02, NULL, NULL);
  
    osKernelStart();  // Start the RTOS scheduler
  
    while (1) {}
}

void StartDefaultTask(void *argument)
{
    for(;;)
    {
        // Wait for event flag to turn the LED on
        osEventFlagsWait(eventoled_onHandle, (1U << 0), osFlagsWaitAny, osWaitForever);

        // Take the semaphore (protecting critical section)
        osSemaphoreAcquire(myBinarySem01Handle, osWaitForever);

        // Turn on the LED (PG13)
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);

        // Delay for 1 second
        osDelay(1000);

        // Turn off the LED (PG13)
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);

        // Release the semaphore
        osSemaphoreRelease(myBinarySem01Handle);
    }
}

void StartTask02(void *argument)
{
    for(;;)
    {
        // Simulate some condition or user action to trigger LED on event
        osDelay(2000);  // Simulate delay for triggering LED action

        // Send message to the queue (could be used for more complex messaging)
        uint16_t msg = 1;
        osMessageQueuePut(led_onHandle, &msg, 0, 0);

        // Set event flag to turn on the LED
        osEventFlagsSet(eventoled_onHandle, (1U << 0));
    }
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOG_CLK_ENABLE();
  
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

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

void Error_Handler(void)
{
    __disable_irq();
    while (1) {}
}
