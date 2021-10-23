/*
 * speed_controller.c
 *
 * Created: 22.10.2021 13:09:25
 *  Author: thoander
 */ 

#include <util/atomic.h>

#include "PID_controller.h"
#include "../speed_estimator/speed_estimator.h"
#include "../timer/timer.h"
#include "../misc/misc.h"

float reference_speed = 0.0;
float Kp = 0.0;
float Ki = 0.0;
float Kd = 0.0;



void PID_controller_set_reference(PID_controller *pid, float ref) {
	pid->reference = ref;
}

void PID_controller_set_parameters(PID_controller *pid, float P, float I, float D, float loop_period) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		pid->Kp = P;
		pid->Ki = I;
		pid->Kd = D;
		pid->loop_period = loop_period;
	}
}

void PID_controller_init(PID_controller *pid) {
	pid->Kp = 0.0;
	pid->Ki = 0.0;
	pid->Kp = 0.0;
	pid->loop_period = 0.0;
	pid->reference = 0.0;
	pid->prev_reference = 0.0;
	pid->error = 0.0;
	pid->prev_error = 0.0;
	pid->integral_error = 0.0;
	pid->max_control_action = 100;
	pid->min_control_action = -100; 
	
}


float PID_controller_get_control_action(PID_controller *pid, float error) {
	
	/*if (abs(error) < 0.1) {
		pid->integral_error = 0; 
		error = 0;
	}*/
	
	// integrate error
	pid->integral_error += error*pid->loop_period;
	
	// compute control action u
	float u;
	float prop = pid->Kp*error;
	float integral = pid->Ki*pid->integral_error;
	float der = pid->Kd*(error - pid->prev_error) / pid->loop_period;
	u = prop + integral + der;
	
	// limit output
	float u_limited = u;
	if (u > pid->max_control_action) {
		u_limited = pid->max_control_action;
		if (pid->Ki != 0) {
			pid->integral_error -= (pid->loop_period / pid->Ki) * (u_limited - u); // anti-windup (Beard & McLain)
		}
		
	} else if (u < pid->min_control_action) {
		u_limited = pid->min_control_action;
		if (pid->Ki != 0) {
			pid->integral_error -= (pid->loop_period / pid->Ki) * (u_limited - u); // anti-windup (Beard & McLain)
		}
	}
	
	// update parameters
	pid->prev_error = error;
	pid->prev_reference = pid->reference;
	
	return u_limited;
}