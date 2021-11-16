/*
 * motor.c
 *
 * Created: 05.10.2021 17:26:30
 *  Author: thoander
 */ 

#include "motor.h"
#include "../pwm/pwm.h"
#include "../../defines.h"
#include "../misc/misc.h"
#include <avr/io.h>

void set_left_motor_dir(int dir);
void set_right_motor_dir(int dir);
float abs(float val);


void motor_init(void) {
	
	// For motor control
	pwm_init();
	
	// Set direction control pins to L298N as outputs
	DDRC |= (1 << OUT1);
	DDRC |= (1 << OUT2);
	DDRC |= (1 << OUT3);
	DDRC |= (1 << OUT4);
}

void set_left_motor_dir(int dir) {
	if (dir == FORWARD) {
		PORTC |= (1 << OUT1);
		PORTC &= ~(1 << OUT2);
	} else {
		PORTC &= ~(1 << OUT1);
		PORTC |= (1 << OUT2);
	}
}

void set_right_motor_dir(int dir) {
	if (dir == FORWARD) {
		PORTC |= (1 << OUT3);
		PORTC &= ~(1 << OUT4);
	} else {
		PORTC &= ~(1 << OUT3);
		PORTC |= (1 << OUT4);
	}
}

void motor_left(float duty) {
	if (duty < 0) {
		set_left_motor_dir(BACKWARD);
	} else {
		set_left_motor_dir(FORWARD);
	}
	float abs_duty = abs(duty);
	pwm_set_duty_cycle_left(abs_duty);	
}

void motor_right(float duty) {
	if (duty < 0) {
		set_right_motor_dir(BACKWARD);
	} else {
		set_right_motor_dir(FORWARD);
	}
	float abs_duty = abs(duty);
	pwm_set_duty_cycle_right(abs_duty);
}

void motor_left_stop(void) {
	PORTC &= ~(1 << OUT1);
	PORTC &= ~(1 << OUT2);
}

void motor_right_stop(void) {
	PORTC &= ~(1 << OUT3);
	PORTC &= ~(1 << OUT4);
}