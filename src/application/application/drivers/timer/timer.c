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
static volatile unsigned int timer_flag = 0;
unsigned int timeout_ms;

void timer_init(unsigned int timeout) {
	
	cli();
	
	timer_flag = 0;
	timeout_ms = timeout;
	
	// Use 8-bit timer 2 for keeping-time
	TCCR2B = 0x00;
	TCNT2 = 0x00;
	OCR2A = 0xF9;
	TCCR2A |= (1 << WGM21) | (1 << CS22); // CTC (Clear timer on compare match with OCR2A), 64 as prescaler
	TCCR2B |= (1 << CS22);
	
	
	// Enable interrupt
	TIMSK2 |= (1 << OCIE2A);
	
	
	/*
	// 0x3E7F (hex) = 15999 (base10)
	// High bytes have to be written before low bytes
	OCR1AH = 0x3E;
	OCR1AL = 0x7F;
	//OCR1A = 15999;
	TCCR1B |= (1 << WGM12) | (1 << CS10); // CTC mode (clear on match with OCR1A), no prescalar
	
	// Enable interrupt
	TIMSK1 |= (1 << OCIE1A);
	//SREG |= (1 << 7);*/
	
	sei();
	
}

unsigned long timer_get_elapsed_ms(void) {
	unsigned long ms;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		ms = elapsed_ms;
	}
	return ms;
}

void timer_reset(void) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		elapsed_ms = 0;
		TCNT2 = 0x00;
		timer_flag = 0;
	}
}

unsigned int timer_timeout(void) {
	unsigned int flag;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		flag = timer_flag;
	}
	return flag;
}

ISR(TIMER2_COMPA_vect) {
	++elapsed_ms;
	if (elapsed_ms >= timeout_ms) {
		timer_flag = 1;
	}
}

