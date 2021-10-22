/*
 * speed_controller.c
 *
 * Created: 22.10.2021 13:09:25
 *  Author: thoander
 */ 

#include "PID_controller.h"
#include "../speed_estimator/speed_estimator.h"
#include "../timer/timer.h"

float reference_speed = 0.0;
float Kp = 0.0;
float Ki = 0.0;
float Kd = 0.0;



void PID_controller_set_reference(PID_controller *pid, float ref) {
	pid->reference = ref;
}

void PID_controller_set_parameters(PID_controller *pid, float P, float I, float D, float loop_period) {
	pid->Kp = P;
	pid->Ki = I;
	pid->Kd = D;
	pid->loop_period = loop_period;
}

void PID_controller_init(PID_controller *pid) {
	pid->Kp = 0.0;
	pid->Ki = 0.0;
	pid->Kp = 0.0;
	pid->loop_period = 0.0;
	pid->reference = 0.0;
	pid->prev_reference = 0.0;
	pid->error = 0.0;
	pid->integral_error = 0.0; 
	
}

float PID_controller_get_control_action(PID_controller *pid) {
	float u = 0.0;
	return u;
}