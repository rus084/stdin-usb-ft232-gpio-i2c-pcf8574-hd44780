/**
 * @file ftdi_i2c.h
 *
 * @date 02.05.2016
 * @author Dmitriy Sidin 
 */

void init_FD(void);
void lcd_HD44780_I2C_write(unsigned char outpt);
void lcdSleep(int period);
void WritePin1(int value);
