/*
 * speed_controller.h
 *
 * Created: 22.10.2021 13:09:46
 *  Author: thoander
 */ 


#ifndef SPEED_CONTROLLER_H_
#define SPEED_CONTROLLER_H_


void set_reference_speed(float ref);

void set_PID_parameters(float P, float I, float D);

void start_PID();

void stop_PID();


#endif /* SPEED_CONTROLLER_H_ */