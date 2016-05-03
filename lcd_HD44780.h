/**
 * @file lcd_HD44780.h
 *
 * @date 13.12.2013
 * @author Andrey Belomutskiy, (c) 2012-2016
 * @author Dmitriy Sidin 
 */

void lcd_HD44780_init(void);
void lcd_HD44780_set_position(unsigned char row, unsigned char column);
void lcd_HD44780_print_char(char data);
void lcd_HD44780_print_string(const char *string);
int getCurrentHD44780row(void);
int getCurrentHD44780column(void);

