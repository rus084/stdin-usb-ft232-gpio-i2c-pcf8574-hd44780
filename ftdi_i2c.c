/**
 * @file ftdi_i2c.c
 *
 * @date 02.05.2016
 * @author Dmitriy Sidin 
 */



#include "ftdi_i2c.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define EFI_I2C_SCL_FD pin2fd
#define EFI_I2C_SDA_FD pin1fd
#define LCD_FD_EXP_ADDR 0x3F

static int pin1fd = 1;
static int pin2fd = 2;



void init_FD(void) {
	int exportfd;
	exportfd = open("/sys/class/gpio/export", O_WRONLY);
	if (exportfd < 0)
		{
			printf("Cannot open GPIO to export\n");
		}
	write(exportfd, "504", 4);
	write(exportfd, "505", 4);
	close(exportfd);


	int directionfd;
	directionfd = open("/sys/class/gpio/gpio504/direction", O_RDWR);
	if (directionfd < 0)
	{
	    printf("Cannot open GPIO direction for 504\n");
	}
	write(directionfd, "out", 4);
	close(directionfd);

	directionfd = open("/sys/class/gpio/gpio505/direction", O_RDWR);
	if (directionfd < 0)
	{
	    printf("Cannot open GPIO direction for 505\n");
	}
	write(directionfd, "out", 4);
	close(directionfd);


	pin1fd = open("/sys/class/gpio/gpio504/value", O_RDWR);
	if (pin1fd < 0)
	{
	    printf("Cannot open GPIO value for 504\n");
	}

	pin2fd = open("/sys/class/gpio/gpio505/value", O_RDWR);
	if (pin1fd < 0)
	{
	    printf("Cannot open GPIO value for 505\n");
	}
}


void WritePin(int fd,int value) {
	char data[2];
	data[0]='1'-value;
	data[1]=0;
	write(fd, data, 2);
}

void WritePin1(int value) {
	char data[2];
	data[0]='1'-value;
	data[1]=0;
	write(pin1fd, data, 2);
	usleep(500);
}

void lcdSleep(int period) {
	usleep(period*50);
}

void lcd_HD44780_I2C_write(unsigned char outpt) {

                WritePin(EFI_I2C_SDA_FD, 1); //start bit
                
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);
                WritePin(EFI_I2C_SDA_FD, LCD_FD_EXP_ADDR & 0x40 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, LCD_FD_EXP_ADDR & 0x20 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, LCD_FD_EXP_ADDR & 0x10 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, LCD_FD_EXP_ADDR & 0x08 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, LCD_FD_EXP_ADDR & 0x04 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, LCD_FD_EXP_ADDR & 0x02 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, LCD_FD_EXP_ADDR & 0x01 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, 1); // r/w bit
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);  
                
                WritePin(EFI_I2C_SDA_FD, 1); // ACK bit
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);  
                

                WritePin(EFI_I2C_SDA_FD, outpt & 0x80 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, outpt & 0x40 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);
                
                WritePin(EFI_I2C_SDA_FD, outpt & 0x20 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, outpt & 0x10 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, outpt & 0x08 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, outpt & 0x04 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, outpt & 0x02 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);

                WritePin(EFI_I2C_SDA_FD, outpt & 0x01 ? 0 : 1);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);
                
                WritePin(EFI_I2C_SDA_FD, 1); // r/w bit
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 1);  
                
                WritePin(EFI_I2C_SDA_FD, 1); // ACK bit
                lcdSleep(10);
                WritePin(EFI_I2C_SCL_FD, 0);
                lcdSleep(10);
                WritePin(EFI_I2C_SDA_FD, 0); // Stop bit
	
}

