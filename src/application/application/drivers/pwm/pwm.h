/*
 * pwm.h
 *
 * Created: 04.10.2021 16:23:08
 *  Author: thoander
 */ 


#ifndef PWM_H_
#define PWM_H_


void pwm_init(void);

void pwm_set_duty_cycle_left(float d);

void pwm_set_duty_cycle_right(float d);


#endif /* PWM_H_ */