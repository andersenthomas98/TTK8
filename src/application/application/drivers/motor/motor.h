/*
 * motor.h
 *
 * Created: 05.10.2021 17:26:43
 *  Author: thoander
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#define FORWARD 1
#define BACKWARD 0


void motor_init(void);

// Set speed and direction of left motor.
// duty is a value between -100 and 100 
void motor_left(float duty);


// Set speed and direction of right motor.
// duty is a value between -100 and 100
void motor_right(float duty);

void motor_left_stop(void);

void motor_right_stop(void);

#endif /* MOTOR_H_ */