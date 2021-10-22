/*
 * speed_controller.c
 *
 * Created: 22.10.2021 13:09:25
 *  Author: thoander
 */ 

#include "speed_controller.h"
#include "speed_estimator.h"
#include "timer.h"

float reference_speed = 0.0;
float Kp = 0.0;
float Ki = 0.0;
float Kd = 0.0;

void set_reference_speed(float ref) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		reference_speed = ref;
	}
}

void set_PID_parameters(float P, float I, float D) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		Kp = P;
		Ki = I;
		Kd = D;
	}
}

void start_PID(){
	
}

void stop_PID() {
	
}