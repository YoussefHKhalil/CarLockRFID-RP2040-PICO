 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include <stdio.h>
#include "pico/stdlib.h"
#include "lcd.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void)
{
	/* Configure the direction for RS and E pins as output pins */
	gpio_init(E);
    gpio_init(RS);
    gpio_set_dir(E,GPIO_OUT);
    gpio_set_dir(RS,GPIO_OUT);       

	sleep_ms(20);	/* LCD Power ON delay always > 15ms */

#if(LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins */
	gpio_init(D4);
    gpio_init(D5);
    gpio_init(D6);
    gpio_init(D7);
    gpio_set_dir(D4,GPIO_OUT);
    gpio_set_dir(D5,GPIO_OUT);
    gpio_set_dir(D6,GPIO_OUT);
    gpio_set_dir(D7,GPIO_OUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 8)
	/* Configure the data port as output port */
	gpio_init(D0);
    gpio_init(D1);
    gpio_init(D2);
    gpio_init(D3);
    gpio_init(D4);
    gpio_init(D5);
    gpio_init(D6);
    gpio_init(D7);
    gpio_set_dir(D0,GPIO_OUT);
    gpio_set_dir(D1,GPIO_OUT);
    gpio_set_dir(D2,GPIO_OUT);
    gpio_set_dir(D3,GPIO_OUT);
    gpio_set_dir(D4,GPIO_OUT);
    gpio_set_dir(D5,GPIO_OUT);
    gpio_set_dir(D6,GPIO_OUT);
    gpio_set_dir(D7,GPIO_OUT);

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(unsigned char command)
{
	gpio_put(RS,false); /* Instruction Mode RS=0 */
	sleep_ms(1); /* delay for processing Tas = 50ns */
	gpio_put(E,true);
	sleep_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_DATA_BITS_MODE == 4)
    gpio_put(D4,GET_BIT(command,4));
    gpio_put(D5,GET_BIT(command,5));
    gpio_put(D6,GET_BIT(command,6));
    gpio_put(D7,GET_BIT(command,7));

	sleep_ms(1); /* delay for processing Tdsw = 100ns */
	gpio_put(E,false); /* Disable LCD E=0 */
	sleep_ms(1); /* delay for processing Th = 13ns */
	gpio_put(E,true); /* Enable LCD E=1 */
	sleep_ms(1); /* delay for processing Tpw - Tdws = 190ns */

    gpio_put(D4,GET_BIT(command,0));
    gpio_put(D5,GET_BIT(command,1));
    gpio_put(D6,GET_BIT(command,2));
    gpio_put(D7,GET_BIT(command,3));
	sleep_ms(1); /* delay for processing Tdsw = 100ns */
	gpio_put(E,false); /* Disable LCD E=0 */
	sleep_ms(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	/* out the required command to the data bus D0 --> D7 */
    gpio_put(D0,GET_BIT(command,0));
    gpio_put(D1,GET_BIT(command,1));
    gpio_put(D2,GET_BIT(command,2));
    gpio_put(D3,GET_BIT(command,3));
    gpio_put(D4,GET_BIT(command,4));
    gpio_put(D5,GET_BIT(command,5));
    gpio_put(D6,GET_BIT(command,6));
    gpio_put(D7,GET_BIT(command,7));
	sleep_ms(1); /* delay for processing Tdsw = 100ns */
	gpio_put(E,false); /* Disable LCD E=0 */
	sleep_ms(1); /* delay for processing Th = 13ns */
#endif
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(unsigned char data)
{
	gpio_put(RS,true); /* Data Mode RS=1 */
	sleep_ms(1); /* delay for processing Tas = 50ns */
	gpio_put(E,true); /* Enable LCD E=1 */
	sleep_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_DATA_BITS_MODE == 4)
	gpio_put(D4,GET_BIT(data,4));
    gpio_put(D5,GET_BIT(data,5));
    gpio_put(D6,GET_BIT(data,6));
    gpio_put(D7,GET_BIT(data,7));

	sleep_ms(1); /* delay for processing Tdsw = 100ns */
	gpio_put(E,false); /* Disable LCD E=0 */
	sleep_ms(1); /* delay for processing Th = 13ns */
	gpio_put(E,true); /* Enable LCD E=1 */
	sleep_ms(1); /* delay for processing Tpw - Tdws = 190ns */

    gpio_put(D4,GET_BIT(data,0));
    gpio_put(D5,GET_BIT(data,1));
    gpio_put(D6,GET_BIT(data,2));
    gpio_put(D7,GET_BIT(data,3));
	sleep_ms(1); /* delay for processing Tdsw = 100ns */
	gpio_put(E,false); /* Disable LCD E=0 */
	sleep_ms(1); /* delay for processing Th = 13ns */


#elif(LCD_DATA_BITS_MODE == 8)
	 /* out the required command to the data bus D0 --> D7 */
    gpio_put(D0,GET_BIT(data,0));
    gpio_put(D1,GET_BIT(data,1));
    gpio_put(D2,GET_BIT(data,2));
    gpio_put(D3,GET_BIT(data,3));
    gpio_put(D4,GET_BIT(data,4));
    gpio_put(D5,GET_BIT(data,5));
    gpio_put(D6,GET_BIT(data,6));
    gpio_put(D7,GET_BIT(data,7));
	sleep_ms(1); /* delay for processing Tdsw = 100ns */
	gpio_put(E,false); /* Disable LCD E=0 */
	sleep_ms(1); /* delay for processing Th = 13ns */
#endif
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str)
{
	unsigned char i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
	/***************** Another Method ***********************
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
	*********************************************************/
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(unsigned char row,unsigned char col)
{
	unsigned char lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(unsigned char row,unsigned char col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   sprintf(buff, "%d", data); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}

bool GET_BIT(unsigned char REG, unsigned char BIT) {
    return (REG & (1 << BIT)) != 0;
}
