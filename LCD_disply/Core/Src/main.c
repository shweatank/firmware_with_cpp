#include "dht11.h"
#include "stm32f4xx_hal.h"
#include "string.h"  // For strlen

// Declare the UART Handle
UART_HandleTypeDef huart1;

// DHT11 initialization
void DHT_init(DHT_t *dht, DHT_Type_t type, TIM_HandleTypeDef *tim, uint16_t timerBusFrequencyMHz, GPIO_TypeDef *gpio, uint16_t pin)
{
    dht->tim = tim;
    dht->gpio = gpio;
    dht->pin = pin;
    dht->type = type;
    dht->cnt = 0;
    dht->time = 0;
    dht->lastCNT = 0;
    dht->dataValid = false;
}

// Read data from DHT11
bool DHT_readData(DHT_t *dht, float *temperature, float *humidity)
{
    // Add your DHT11 reading logic here
    *temperature = 25.0;  // Set mock temperature
    *humidity = 60.0;     // Set mock humidity

    return true;
}

// USART initialization
void USART1_Init(void)
{
    // Configure USART1
    huart1.Instance = USART1;  // Select USART1
    huart1.Init.BaudRate = 115200;  // Set baud rate
    huart1.Init.WordLength = UART_WORDLENGTH_8B;  // 8 bits data length
    huart1.Init.StopBits = UART_STOPBITS_1;  // 1 stop bit
    huart1.Init.Parity = UART_PARITY_NONE;  // No parity
    huart1.Init.Mode = UART_MODE_TX_RX;  // Enable TX and RX
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;  // No hardware flow control
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;  // Over-sample by 16

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();  // Handle error
    }
}

// USART transmission function
void USART_Transmit(const char *data)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)data, strlen(data), HAL_MAX_DELAY);  // Transmit data over USART
}

// ADC conversion and log function
void ADC_Conversion_And_Log(void)
{
    uint32_t adcValue = 1234;  // Mock ADC value

    // Log the ADC value via USART
    char logBuffer[100];
    snprintf(logBuffer, sizeof(logBuffer), "ADC Value: %lu\r\n", adcValue);
    USART_Transmit(logBuffer);

    // Read data from DHT11 and log it
    float temperature, humidity;
    if (DHT_readData(&dht, &temperature, &humidity))
    {
        snprintf(logBuffer, sizeof(logBuffer), "Temperature: %.2f C, Humidity: %.2f %%\r\n", temperature, humidity);
        USART_Transmit(logBuffer);
    }
}

int main(void)
{
    HAL_Init();  // Initialize the HAL Library

    // Initialize USART
    USART1_Init();

    // Initialize DHT11
    DHT_t dht;
    DHT_init(&dht, DHT_TYPE, &htim2, 16, GPIOB, GPIO_PIN_1);

    // ADC Conversion and Log
    ADC_Conversion_And_Log();

    // Main loop
    while (1)
    {
        // You can continuously perform ADC conversions and log here
    }
}
