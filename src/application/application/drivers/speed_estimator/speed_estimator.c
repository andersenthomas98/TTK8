/*
 * speed_estimator.c
 *
 * Created: 07.10.2021 13:33:50
 *  Author: thoander
 */ 

#include "../../defines.h"
#include "../encoder/encoder.h"
#include "../timer/timer.h"
#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <math.h>
#include <stdio.h>


int ticks_right = 0;
int ticks_left = 0;
int prev_ticks_right = 0;
int prev_ticks_left = 0;
float rad_per_s_left = 0;
float rad_per_s_right = 0;


// Should be updated if timer is adjusted!
const float encoder_measurement_period = 0.02;//0.01; //0.05;

void speed_estimator_init(void) {
	
	encoder_init();
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		ticks_right = encoder_get_accumulated_ticks_right();
		ticks_left = encoder_get_accumulated_ticks_left();	
	}
	
	/*
	
	measurement_period = (2^8*prescaler) / F_CPU * OCR2A/(2^8-1)
	
	(2^8*1024) / (16000000) * 255/255 = 0.016384
	
	OCR1A = measurement_period * F_CPU * (2^16-1) / (2^16*prescalar)
	
	*/
	cli();
	
	/*
	// Timer2 for measuring encoder ticks at set period
	TCCR2B = 0x00;
	TCNT2 = 0x00;
	OCR2A = 0xFF;
	TCCR2A |= (1 << WGM21) | (1 << CS21) | (1 << CS00); // CTC (Clear timer on compare match with OCR2A), 1024 as prescaler
	TCCR2B |= (1 << CS22);
	
	
	// Enable interrupt
	TIMSK2 |= (1 << OCIE2A);
	*/
	
	// 16-bit Timer1
	OCR1AH = 0x04;
	OCR1AL = 0xE1;
	//OCR1A = 15999;
	TCCR1B |= (1 << WGM12) | (1 << CS12); // CTC mode (clear on match with OCR1A), 256 prescalar
	
	// Enable interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	sei();
}

float speed_estimator_right_rad_per_s() {
	float rad_per_s;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		rad_per_s = rad_per_s_right;
	}
	return rad_per_s;
}

float speed_estimator_left_rad_per_s() {
	float rad_per_s;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		rad_per_s = rad_per_s_left;
	}
	return rad_per_s;
}

/*
ISR(TIMER2_COMPA_vect) {
	// Should be updated if timer is adjusted!
	float encoder_measurement_period = 0.016384;
	
	int ticks_right = encoder_get_accumulated_ticks_right();
	// (prev_ticks_right != ticks_right) {
	//	prev_ticks_right = ticks_right;
	//} 
	prev_ticks_right = ticks_right;
	right_rad_per_s = 2.0*PI*((float)ticks_right - (float)prev_ticks_right) / ((float)TICKS_PER_ROT*encoder_measurement_period); 
	
	
	int ticks_left = encoder_get_accumulated_ticks_left();
	//if (prev_ticks_left != ticks_left) {
	//	prev_ticks_left = ticks_left;
	//}
	prev_ticks_left = ticks_left;
	left_rad_per_s = 2.0*PI*((float)ticks_left - (float)prev_ticks_left) / ((float)TICKS_PER_ROT*encoder_measurement_period);
	
}*/

ISR(TIMER1_COMPA_vect) {
	prev_ticks_right = ticks_right;
	ticks_right = encoder_get_accumulated_ticks_right();
	rad_per_s_right = 2.0*PI*((float)ticks_right - (float)prev_ticks_right) / ((float)TICKS_PER_ROT*encoder_measurement_period);
	
	prev_ticks_left = ticks_left;
	ticks_left = encoder_get_accumulated_ticks_left();
	rad_per_s_left = 2.0*PI*((float)ticks_left - (float)prev_ticks_left) / ((float)TICKS_PER_ROT*encoder_measurement_period);
	//printf("ISR: %d | %d\n\r", ticks_left, prev_ticks_left);
}

