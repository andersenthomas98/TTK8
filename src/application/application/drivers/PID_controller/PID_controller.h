/*
 * speed_controller.h
 *
 * Created: 22.10.2021 13:09:46
 *  Author: thoander
 */ 


#ifndef SPEED_CONTROLLER_H_
#define SPEED_CONTROLLER_H_

typedef struct {
	float reference;
	float prev_reference;
	float error;
	float prev_error;
	float integral_error;
	float Kp;
	float Ki;
	float Kd;
	float loop_period;
	float prev_control_action;
	float max_control_action;
	float min_control_action;
}PID_controller;


void PID_controller_init(PID_controller *pid);

void PID_controller_set_reference(PID_controller *pid, float ref);

void PID_controller_set_parameters(PID_controller *pid, float P, float I, float D, float loop_period);

float PID_controller_get_control_action(PID_controller *pid, float error);


#endif /* SPEED_CONTROLLER_H_ */