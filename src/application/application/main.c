/*
 * main.c
 *
 * Created: 10/4/2021 12:17:52 PM
 *  Author: thoander
 */ 

#define F_CPU 16000000UL

#include <xc.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "defines.h"

#include "drivers/usart/usart.h"
#include "drivers/encoder/encoder.h"


int main(void)
{
	usart_init(UBRR);
	encoder_init();
	
	printf("Starting application\n\r");
	
	//DDRB = (1<<BUILTIN_LED); //PB7 is digital pin 13 (LED), set as output
	//PORTB = (1<<BUILTIN_LED); //Set PB7 high to turn on LED
	
	while(1)
	{
		/*
		_delay_ms(1000);
		printf("off\n\r");
		PORTB = ~(1<<BUILTIN_LED);
		_delay_ms(3000);
		printf("on\n\r");
		PORTB = (1<<BUILTIN_LED);
		*/
		int ticksL = encoder_get_accumulated_ticks_left();
		int ticksR = encoder_get_accumulated_ticks_right();
		printf("L = %d; R = %d\n\r", ticksL, ticksR);
		
	}
}