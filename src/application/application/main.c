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
#include <string.h>

#include "drivers/usart/usart.h"
#include "drivers/encoder/encoder.h"
#include "drivers/motor/motor.h"
#include "drivers/timer/timer.h"
#include "drivers/speed_estimator/speed_estimator.h"
#include "drivers/PID_controller/PID_controller.h"

int main(void)
{
	usart_init(UBRR);
	speed_estimator_init(850, 850);

	motor_init();

	
	float T = 0.02; // Control loop period [s]
	timer_init(T*1000); 
	
	printf("Starting application\n\r");
	
	
	PID_controller left_motor;
	PID_controller right_motor;
	PID_controller_init(&left_motor);
	PID_controller_init(&right_motor);
	//PID_controller_set_parameters(&left_motor, 10.0, 50.0, 0.0, 0.05);
	//PID_controller_set_parameters(&right_motor, 10.0, 50.0, 0.0, 0.05);
	PID_controller_set_parameters(&left_motor, 10.0, 50.0, 0.0, T);
	PID_controller_set_parameters(&right_motor, 10.0, 50.0, 0.0, T);
	
	
	float left_error_rps; // left wheel speed error [rad/s]
	float left_speed_rps; // left wheel speed [rad/s]
	float left_speed_ref_rps = DEG2RAD*30; // left wheel reference speed [rad/s]. 9.86 rad/s = 565 deg/s is max speed.
	float left_u; // left wheel speed control action
	
	float right_error_rps; // right wheel error [rad/s]
	float right_speed_rps;
	float right_speed_ref_rps = DEG2RAD*30;
	float right_u;
	int i = 0;
	int flag = 0;
	unsigned long time=0;
	
	
	
	while(1)
	{
		// wheel speed control loop
		if (timer_timeout()) {
			timer_reset();
	
			left_speed_rps = speed_estimator_left_rad_per_s();
			left_error_rps = left_speed_ref_rps - left_speed_rps;
			left_u = PID_controller_get_control_action(&left_motor, left_error_rps);
			motor_left(left_u);
			
			
			right_speed_rps = speed_estimator_right_rad_per_s();
			right_error_rps = right_speed_ref_rps - right_speed_rps;
			right_u = PID_controller_get_control_action(&right_motor, right_error_rps);
			motor_right(right_u);
			
			time = timer_get_elapsed_ms();
			
			flag = 1;
		} 
		if (flag) {
			printf("{\"t\":%lu,\"l\":{\"ref\":%.2f,\"y\":%.2f,\"u\":%.2f},\"r\":{\"ref\":%.2f,\"y\":%.2f,\"u\":%.2f}}\n\r", time, left_speed_ref_rps, left_speed_rps, left_u, right_speed_ref_rps, right_speed_rps, right_u);
			//printf("{\"t\":%lu,\"l\":{\"ref\":%f,\"y\":%f,\"u\":%f}\n", time, left_speed_ref_rps, left_speed_rps, left_u);
			//printf("{\"t\":%lu ,\"s\":%f}\n", time, left_speed_rps);
			//send_buffer[i] = {time, left_speed_ref_rps, left_speed_rps, left_u, right_speed_ref_rps, right_speed_rps, right_u};	
			flag = 0;
		}
	}
	
	
	return 0;
}