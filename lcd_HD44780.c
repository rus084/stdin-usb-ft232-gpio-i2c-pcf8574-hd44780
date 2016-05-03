/**
 * @file lcd_HD44780.cpp
 * @brief HD44780 character display driver
 *
 * see http://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
 * @date 13.12.2013
 * @author Andrey Belomutskiy, (c) 2012-2016
 * @author Dmitriy Sidin 
 */


#include "lcd_HD44780.h"
#include "ftdi_i2c.h"



static unsigned char txbuf[1];



enum {
	LCD_HD44780_DISPLAY_CLEAR = 0x01,
	LCD_HD44780_SHIFT_CURSOR_RIGHT = 0x06,
	LCD_HD44780_DISPLAY_ON = 0x0C,
	LCD_HD44780_4_BIT_BUS = 0x20,
	LCD_HD44780_RESET = 0x30,
	LCD_HD44780_DDRAM_ADDR = 0x80,

//	LCD_2X16_8_BIT_BUS = 0x30,
//	LCD_2X16_LINE_ONE = 0x20,
//	LCD_2X16_LINES_TWO = 0x28,
//	LCD_2X16_FONT_5X8 = 0x20,
//	LCD_2X16_FONT_5X10 = 0x24,
//	LCD_2X16_DISPLAY_HOME = 0x02,
//	LCD_2X16_DISPLAY_RIGHT = 0x1C,
//	LCD_2X16_DISPLAY_LEFT = 0x18,
//	LCD_2X16_DISPLAY_SHIFT = 0x05,
//	LCD_2X16_CURSOR_ON = 0x0A,
//	LCD_2X16_CURSOR_BLINK = 0x09,
//	LCD_2X16_CURSOR_RIGHT = 0x14,
//	LCD_2X16_CURSOR_LEFT = 0x10,
//	LCD_2X16_SHIFT_LEFT = 0x04,
//	LCD_2X16_CGRAM_ADDR = 0x40,
//	LCD_2X16_BUSY_FLAG = 0x80,
//	LCD_2X16_COMMAND = 0x01,
//	LCD_2X16_DATA = 0x00,
} lcd_HD44780_command;

// http://web.alfredstate.edu/weimandn/lcd/lcd_addressing/lcd_addressing_index.html
static const int lineStart[] = { 0, 0x40, 0x14, 0x54 };

static int currentRow = 0;
static int currentColumn = 0;



static void lcd_HD44780_write(unsigned char data) {

          
          
		//	LCD D4_pin -> P4
		//	LCD D5_pin -> P5
		//	LCD D6_pin -> P6
		//	LCD D7_pin -> P7
		//	LCD Pin RS -> P0
		//	LCD Pin RW -> P1
		//	LCD Pin E  -> P2
                //      LCD Light  -> P3
          
             txbuf[0] = txbuf[0] & 0x0F ;	
             txbuf[0] = txbuf[0] | (data & 0xF0) ;
		txbuf[0] = txbuf[0] | 0x04 ;
		lcd_HD44780_I2C_write(txbuf[0]);
		txbuf[0] = txbuf[0] & 0xFB ;
		lcd_HD44780_I2C_write(txbuf[0]);


}


static void ClearPad_HD44780_RS(void) {
  txbuf[0] = txbuf[0] & 0xFE;
}

static void SetPad_HD44780_RS(void) {
  txbuf[0] = txbuf[0] | 0x01;
}

//-----------------------------------------------------------------------------
void lcd_HD44780_write_command(unsigned char data) {
  
	ClearPad_HD44780_RS();

	lcd_HD44780_write(data);
	lcd_HD44780_write(data << 4);
}

//-----------------------------------------------------------------------------
void lcd_HD44780_write_data(unsigned char data) {
	SetPad_HD44780_RS();

	lcd_HD44780_write(data);
	lcd_HD44780_write(data << 4);
	currentColumn++;
}

//-----------------------------------------------------------------------------
void lcd_HD44780_set_position(unsigned char row, unsigned char column) {
	currentRow = row;
	currentColumn = column;
	lcd_HD44780_write_command(LCD_HD44780_DDRAM_ADDR + lineStart[row] + column);
}

int getCurrentHD44780row(void) {
	return currentRow;
}

int getCurrentHD44780column(void) {
	return currentColumn;
}

void toggleBackLight (void) {
	txbuf[0] = txbuf[0] & 0x08 ? txbuf[0] & 0xf7 : txbuf[0] | 0x08; 
	lcd_HD44780_write(txbuf[0]);
}

void lcd_HD44780_print_char(char data) {

	switch (data) {
	case '\n':
  		lcd_HD44780_set_position(++currentRow, 0);
  		break;
	case 27:
		toggleBackLight();
		break;
	default:
  		if (currentColumn>19) lcd_HD44780_set_position(++currentRow, 0);
		if (currentRow>3) lcd_HD44780_set_position(0, 0);
		lcd_HD44780_write_data(data);
  		break;
	}

}

void lcd_HD44780_print_string(const char* string) {
	while (*string != 0x00)
		lcd_HD44780_print_char(*string++);
}


void lcd_HD44780_init(void) {

	init_FD();

	txbuf[0]=0x08;
	lcdSleep(1000); // LCD needs some time to wake up
	lcd_HD44780_write(LCD_HD44780_RESET); // reset 1x
	txbuf[0]=0x08;
	lcdSleep(500);
	lcd_HD44780_write(LCD_HD44780_RESET); // reset 2x
	lcd_HD44780_write(LCD_HD44780_RESET); // reset 3x

	lcd_HD44780_write(LCD_HD44780_4_BIT_BUS);	// 4 bit, 2 line
	lcdSleep(200);

	lcd_HD44780_write(LCD_HD44780_4_BIT_BUS);	// 4 bit, 2 line
	lcd_HD44780_write(0x80);
	lcdSleep(200);

	lcd_HD44780_write_command(0x08);	// display and cursor control
	lcdSleep(100);

	//lcd_HD44780_write_command(LCD_HD44780_DISPLAY_CLEAR);
	lcdSleep(100);

	lcd_HD44780_write_command(LCD_HD44780_SHIFT_CURSOR_RIGHT);
	lcdSleep(100);

	lcd_HD44780_write_command(LCD_HD44780_DISPLAY_ON);

	lcd_HD44780_set_position(0, 0);
}
