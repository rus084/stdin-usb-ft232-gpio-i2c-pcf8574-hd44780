/**
 * @file main.c
 *
 * @date 02.05.2016
 * @author Dmitriy Sidin 
 */


#include "lcd_HD44780.h"

#include <fcntl.h>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int getch( ) {
struct termios oldt,
newt;
int ch;
tcgetattr( STDIN_FILENO, &oldt );
newt = oldt;
newt.c_lflag &= ~( ICANON | ECHO );
tcsetattr( STDIN_FILENO, TCSANOW, &newt );
ch = getchar();
tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
return ch;
}

int main(void) {

lcd_HD44780_init();
	setbuf(stdin, NULL);
	int symbol;
while (0) {
	lcd_HD44780_print_char(27);
}
	while ((symbol = getch()) != EOF) {
	    lcd_HD44780_print_char(symbol);
	}

}
