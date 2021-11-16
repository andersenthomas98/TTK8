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

void speed_estimator_test() {
	
	usart_init(UBRR);
	speed_estimator_init(850, 850);
	motor_init();
	timer_init(10000);
	
	unsigned long time = 0;
	float left_speed_rps; // left wheel speed [rad/s]
	
	while(1) {
		motor_left(10);
		left_speed_rps = speed_estimator_left_rad_per_s();
		time = timer_get_elapsed_ms();
		printf("{\"t\":%lu,\"s\":%.3f}\n", time, left_speed_rps);
		if (timer_timeout()) {
			motor_left_stop();
			return 0;
		}
	}
}

void encoder_motor_test() {
	
	long ticks_left = 0;
	long ticks_right = 0;
	int speeds[6] = {10, -10, 50, -50, 100, -100};
	int j = 0;
	unsigned long time = 0;
	
	while(1) {
		motor_left(speeds[j]);
		motor_right(speeds[j]);
		ticks_left = encoder_get_accumulated_ticks_left();
		ticks_right = encoder_get_accumulated_ticks_right();
		time = timer_get_elapsed_ms();
		printf("{\"l\":%ld,\"r\":%ld,\"s\":%d,\"t\": %lu}\n", ticks_left, ticks_right, speeds[j], time);
		if (timer_timeout()) {
			j++;
			motor_left_stop();
			motor_right_stop();
			if (j>5) {
				return 0;
			}
			timer_reset();
		}
	}
}



int main(void)
{
	usart_init(UBRR);
	speed_estimator_init(840, 850);

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
	float left_speed_ref_rps = DEG2RAD*500; // left wheel reference speed [rad/s]. 9.86 rad/s = 565 deg/s is max speed.
	float left_u; // left wheel speed control action
	
	float right_error_rps; // right wheel error [rad/s]
	float right_speed_rps;
	float right_speed_ref_rps = DEG2RAD*500;
	float right_u;

	int send_flag = 0;
	unsigned long time=0;
	unsigned long change_ref_time = 10000;
	
	float refs[2] = {DEG2RAD*(-500), DEG2RAD*(100)};

	int i = 0;
	
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
			
			if (time >= change_ref_time) {
				change_ref_time = time + 5000;
				left_speed_ref_rps = refs[i];
				right_speed_ref_rps = refs[i];
				i++;
			}
			if (i > 2) {
				motor_left_stop();
				motor_right_stop();
				return 0;
			}
			
			send_flag = 1;
		} 
		
		if (send_flag) {
			printf("{\"t\":%lu,\"l\":{\"ref\":%.2f,\"y\":%.2f,\"ulim\":%.2f},\"r\":{\"ref\":%.2f,\"y\":%.2f,\"ulim\":%.2f}}\n", time, left_speed_ref_rps, left_speed_rps, left_u, right_speed_ref_rps, right_speed_rps, right_u);
			send_flag = 0;
		}
	}
	
	
	return 0;
}