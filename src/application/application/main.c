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

#include "drivers/usart/usart.h"

int main(void)
{
	usart_init(UBRR);
	
	printf("Starting application\n\r");
	
	DDRB = (1<<PORTB5); //PB7 is digital pin 13 (LED), set as output
	PORTB = (1<<PORTB5); //Set PB7 high to turn on LED
	
	while(1)
	{
		_delay_ms(1000);
		printf("off\n\r");
		PORTB = ~(1<<PORTB5);
		_delay_ms(3000);
		printf("on\n\r");
		PORTB = (1<<PORTB5);
		
	}
}