/*
 * pwm.c
 *
 * Created: 04.10.2021 16:22:54
 *  Author: thoander
 */ 

#include <avr/io.h>
#include "../../defines.h"
#include "pwm.h"

void pwm_init(void) {
	
	// Set as output (one for each wheel)
	DDRD |= (1 << PWM1);
	DDRD |= (1 << PWM2);
	
	// Compare output mode: Fast PWM mode
	// Clear OC0A/B on compare match, set OC0A/B at BOTTOM (mode 3)
	/*
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS02) | (1 << CS00); // 1024 prescalar
	*/
	
	// Phase correct PWM mode
	// PWM frequency will be (with no prescaler) 31kHz (outside audible spectrum)
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
	TCCR0B |= (1 << CS00); // no pre-scaling
	
	
}

void pwm_set_duty_cycle_left(float d) {
	// value should be between 0-255
	float value = d / 100.0 * (255 - MIN_PWM_DUTY_LEFT) + MIN_PWM_DUTY_LEFT;
	OCR0A = (uint8_t)value;
}

void pwm_set_duty_cycle_right(float d) {
	
	float value = d / 100.0 * (255 - MIN_PWM_DUTY_RIGHT) + MIN_PWM_DUTY_RIGHT;
	printf("%d\n\r", (uint8_t) value);
	OCR0B = (uint8_t)value;
}