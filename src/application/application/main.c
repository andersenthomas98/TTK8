/*
 * main.c
 *
 * Created: 10/4/2021 12:17:52 PM
 *  Author: thoander
 */ 

#include "defines.h"

#include <xc.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "drivers/usart/usart.h"
#include "drivers/encoder/encoder.h"
#include "drivers/motor/motor.h"
//#include "drivers/timer/timer.h"
#include "drivers/speed_estimator/speed_estimator.h"

int main(void)
{
	usart_init(UBRR);
	motor_init();
	//timer_init();
	speed_estimator_init();
	//encoder_init();
	
	printf("Starting application\n\r");
	
	//DDRB = (1<<BUILTIN_LED); //PB7 is digital pin 13 (LED), set as output
	//PORTB = (1<<BUILTIN_LED); //Set PB7 high to turn on LED
	motor_left(100);
	while(1)
	{
		/*
		_delay_ms(1000);
		printf("off\n\r");
		PORTB = ~(1<<BUILTIN_LED);
		_delay_ms(3000);
		printf("on\n\r");
		PORTB = (1<<BUILTIN_LED);
		int ticksL = encoder_get_accumulated_ticks_left();
		int ticksR = encoder_get_accumulated_ticks_right();
		printf("L = %d; R = %d\n\r", ticksL, ticksR);*/
		//motor_left(100);
		//_delay_ms(2000);
		//motor_left(-60);
		//_delay_ms(2000);
		
		float l = speed_estimator_left_rad_per_s();
		//int enc = encoder_get_accumulated_ticks_left();
		//printf("%f\n\r", l);
	}
}