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
	PID_controller_set_parameters(&left_motor, 10.0, 50.0, 0.0, 0.05);
	
	
	float left_error_rps; // left wheel speed error [rad/s]
	float left_speed_rps; // left wheel speed [rad/s]
	float left_speed_ref_rps = DEG2RAD*550; // left wheel reference speed [rad/s]. 9.86 rad/s = 565 deg/s is max speed.
	float left_u; // left wheel speed control action
	
	float right_error_rps; // right wheel error [rad/s]
	int i = 0;
	int flag = 0;
	
	while(1)
	{
		// wheel speed control loop
		if (timer_timeout()) {
			timer_reset();
	
			left_speed_rps = speed_estimator_left_rad_per_s();
			left_error_rps = left_speed_ref_rps - left_speed_rps;
			left_u = PID_controller_get_control_action(&left_motor, left_error_rps);
			motor_left(left_u);
			
			
			i++;
			if (i >=100) {
				if (!flag) {
					left_speed_ref_rps = -DEG2RAD*550;
					flag = 1;
				} else {
					left_speed_ref_rps = DEG2RAD*550;
					flag = 0;
				}
				i = 0;
			}
			printf("%f | %f\n\r", left_motor.integral_error, left_u);
			
			
		}
	}
}