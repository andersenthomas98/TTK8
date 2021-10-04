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
	// Compare output mode: Fast PWM mode
	
	// Set as output
	DDRD |= (1 << PWM1);
	
	// Clear OC0A on compare match, set OC0A at BOTTOM (mode 3)
	TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS00); // No prescaling
}

void pwm_set_duty_cycle(int d) {
	// value should be between 0-255
	int value = 255/100 * d;
	OCR0A = value;
}