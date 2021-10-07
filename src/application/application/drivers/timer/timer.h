/*
 * timer.h
 *
 * Created: 05.10.2021 19:12:25
 *  Author: thoander
 */ 


#ifndef TIMER_H_
#define TIMER_H_

// To generate a tick every 1 ms, a 16MHz oscillator needs to count 16000 cycles.
// Thus, we could use the 16-bit Timer1 (without the prescaler), and set OCR1A or ICR1 to 15999.
// CTC mode


void timer_init(void);

unsigned long timer_get_elapsed_ms(void);


#endif /* TIMER_H_ */