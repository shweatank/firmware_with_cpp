#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>

// USART1 TX: PA9, RX: PA10
void USART_Init(void);
void USART_SendChar(char c);
void USART_SendString(char *str);
float calculate_area(int shape_type);

int main(void)
{
    // Initialize USART
    USART_Init();

    // Variables for input
    char input;
    float area;

    // Send a prompt to the user
    USART_SendString("Enter 1 for Circle, 2 for Rectangle, 3 for Triangle:\r\n");

    // Main loop
    while (1)
    {
        // Receive user input from USART
        input = USART_ReceiveChar();

        // Check the shape type and calculate the area
        if (input == '1') {
            // Area of Circle
            USART_SendString("Enter radius of Circle: ");
            float radius = (float)USART_ReceiveInt();
            area = calculate_area(1, radius);
            USART_SendString("Area of Circle: ");
        }
        else if (input == '2') {
            // Area of Rectangle
            USART_SendString("Enter length and width of Rectangle: ");
            float length = (float)USART_ReceiveInt();
            float width = (float)USART_ReceiveInt();
            area = calculate_area(2, length, width);
            USART_SendString("Area of Rectangle: ");
        }
        else if (input == '3') {
            // Area of Triangle
            USART_SendString("Enter base and height of Triangle: ");
            float base = (float)USART_ReceiveInt();
            float height = (float)USART_ReceiveInt();
            area = calculate_area(3, base, height);
            USART_SendString("Area of Triangle: ");
        }

        // Send the calculated area back to the serial monitor
        char result[50];
        sprintf(result, "%.2f\r\n", area);
        USART_SendString(result);
    }
}

// USART Initialization
void USART_Init(void) {
    // Set up USART1 for communication on PA9 (TX) and PA10 (RX)
    // Code for USART initialization here
}

// Send a single character via USART
void USART_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE));  // Wait until transmit buffer is empty
    USART1->DR = c;
}

// Send a string via USART
void USART_SendString(char *str) {
    while (*str) {
        USART_SendChar(*str++);
    }
}

// Calculate area based on the shape type
float calculate_area(int shape_type, float param1, float param2) {
    if (shape_type == 1) {
        // Circle area: A = π * r^2
        return 3.1416 * param1 * param1;
    } else if (shape_type == 2) {
        // Rectangle area: A = length * width
        return param1 * param2;
    } else if (shape_type == 3) {
        // Triangle area: A = 0.5 * base * height
        return 0.5 * param1 * param2;
    }
    return 0;
}

// Receive a single character via USART
char USART_ReceiveChar(void) {
    while (!(USART1->SR & USART_SR_RXNE));  // Wait for data to be received
    return USART1->DR;
}

// Receive an integer via USART (example for base or height)
int USART_ReceiveInt(void) {
    int number = 0;
    char ch;
    while (1) {
        ch = USART_ReceiveChar();
        if (ch == '\r') break;  // End of input
        number = number * 10 + (ch - '0');
    }
    return number;
}
