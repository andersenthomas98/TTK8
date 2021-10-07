/*
 * timer.c
 *
 * Created: 05.10.2021 19:12:15
 *  Author: thoander
 */ 

// To generate a tick every 1 ms, a 16MHz oscillator needs to count 16000 cycles.
// Thus, we could use the 16-bit Timer1 (without the prescaler), and set OCR1A or ICR1 to 15999.
// CTC mode

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

static volatile unsigned long elapsed_ms = 0;

void timer_init(void) {
	
	cli();
	
	// 0x3E7F (hex) = 15999 (base10)
	// High bytes have to be written before low bytes
	OCR1AH = 0x3E;
	OCR1AL = 0x7F;
	//OCR1A = 15999;
	TCCR1B |= (1 << WGM12) | (1 << CS10); // CTC mode (clear on match with OCR1A), no prescalar
	
	// Enable interrupt
	TIMSK1 |= (1 << OCIE1A);
	//SREG |= (1 << 7);
	sei();
	
}

unsigned long timer_get_elapsed_ms(void) {
	unsigned long ms;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		ms = elapsed_ms;
	}
	return ms;
}
/*
ISR(TIMER1_COMPA_vect) {
	++elapsed_ms;
}*/

