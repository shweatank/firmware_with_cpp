#include "lcd_i2c.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;  // Change if using another I2C peripheral

void lcd_send_cmd(char cmd) {
    char data_u = (cmd & 0xF0);
    char data_l = ((cmd << 4) & 0xF0);
    uint8_t data_t[4] = {data_u | 0x0C, data_u | 0x08, data_l | 0x0C, data_l | 0x08};
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDRESS, data_t, 4, 100);
}

void lcd_send_data(char data) {
    char data_u = (data & 0xF0);
    char data_l = ((data << 4) & 0xF0);
    uint8_t data_t[4] = {data_u | 0x0D, data_u | 0x09, data_l | 0x0D, data_l | 0x09};
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDRESS, data_t, 4, 100);
}

void lcd_clear() {
    lcd_send_cmd(0x01);  // Clear display
    HAL_Delay(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t pos[] = {0x80, 0xC0};  // Row addresses
    lcd_send_cmd(pos[row] + col);
}

void lcd_send_string(char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_init() {
    HAL_Delay(50);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20);
    HAL_Delay(10);

    lcd_send_cmd(0x28);  // Function Set: 4-bit mode, 2 lines, 5x8 font
    HAL_Delay(1);
    lcd_send_cmd(0x0C);  // Display ON, Cursor OFF
    HAL_Delay(1);
    lcd_send_cmd(0x06);  // Entry Mode: Shift cursor right
    HAL_Delay(1);
    lcd_send_cmd(0x01);  // Clear display
    HAL_Delay(2);
}
