/*
 * encoder.c
 *
 * Created: 04.10.2021 12:53:27
 *  Author: thoander
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../../defines.h"
#include "encoder.h"

int encoder_ticks_left = 0;
int encoder_ticks_right = 0;

void encoder_init(void) {
	
	// Set digital inputs with internal pull-up (unsure if internal pull-up should be used)
	DDRD &= ~(1 << ENCA1);
	PORTD |= (1 << ENCA1);
	
	DDRD &= ~(1 << ENCA2);
	PORTD |= (1 << ENCA2);
	
	// Rising edge of INT0 and INT1 will generate an interrupt request
	EICRA |= (1 << ISC00) | (1 << ISC01) | (1 << ISC10) | (1 << ISC11);
	EIMSK |= (1 << INT0) | (1 << INT1);
	
	// Enable global interrupts
	sei();
	
	
}

int encoder_read_tick(int encoder_pin) {
	if (PIND & (1<<encoder_pin)) {
		return 1;
	}
	return 0;
}

int encoder_get_accumulated_ticks_left(void) {
	return encoder_ticks_left;
}

int encoder_get_accumulated_ticks_right(void) {
	return encoder_ticks_right;
}

// Interrupt service routine for INT0
// Triggered on rising edge of channel A encoder signal for left wheel
ISR(INT0_vect) {
	int encb1 = encoder_read_tick(ENCB1);
	if (encb1) {
		encoder_ticks_left++;
	} else {
		encoder_ticks_left--;
	}
}

// Interrupt service routine for INT1
// Triggered on rising edge of channel A encoder signal for right wheel
ISR(INT1_vect) {
	int encb2 = encoder_read_tick(ENCB2);
	if (encb2) {
		encoder_ticks_right++;
		} 
	else {
		encoder_ticks_right--;
	}
}