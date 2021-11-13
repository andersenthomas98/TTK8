/*
 * main.c
 *
 * Created: 11/13/2021 2:12:55 PM
 *  Author: thoander
 */ 

#include <xc.h>

#include <stdio.h>
#include "defines.h"
#include <util/delay.h>
#include "drivers/usart/usart.h"
#include "drivers/encoder/encoder.h"

int main(void) {
	
	usart_init(UBRR);
	encoder_init();
	_delay_ms(1000);
	
	while(1) {
		long left = encoder_get_accumulated_ticks_left();
		long right =  encoder_get_accumulated_ticks_right();
		printf("left: %ld\t right: %ld\n\r", left, right);
		_delay_ms(100);
	}
	
	return 0;
}