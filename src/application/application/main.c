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
#include "drivers/timer/timer.h"
#include "drivers/speed_estimator/speed_estimator.h"
#include "drivers/PID_controller/PID_controller.h"

int main(void)
{
	usart_init(UBRR);
	speed_estimator_init();
	motor_init();

	//encoder_init();
	
	timer_init(50); // Set control loop period to 50 ms (Obs: Should check if code takes longer time to run!)
	
	printf("Starting application\n\r");
	
	
	PID_controller left_motor;
	PID_controller_init(&left_motor);
	PID_controller_set_parameters(&left_motor, 10.0, 10.0, 0.0, 0.05);
	
	
	float left_error_rps; // left wheel error [rad/s]
	float left_speed_rps; // left wheel speed [rad/s]
	float left_speed_ref_rps = DEG2RAD*360; // left wheel reference speed [rad/s]
	float left_u; // left wheel speed control action
	
	float right_error_rps; // right wheel error [rad/s]
	
	while(1)
	{
		// wheel speed control loop
		if (timer_timeout()) {
			timer_reset();
			
			left_speed_rps = speed_estimator_left_rad_per_s();
			left_error_rps = left_speed_ref_rps - left_speed_rps;
			left_u = PID_controller_get_control_action(&left_motor, left_error_rps);
			motor_left(left_u);
			
			printf("%f\n\r", left_speed_rps);
			
			
			
			
		}
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
		
		//unsigned long t = timer_get_elapsed_ms();
		//printf("%lu\n\r", t);
	}
}