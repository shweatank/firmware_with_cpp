#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f4xx_hal.h"  // Change according to your STM32 series

#define LCD_I2C_ADDRESS 0x27 << 1  // I2C Address (change to 0x3F if needed)

// LCD Functions
void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);

#endif
