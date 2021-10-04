/*
 * usart.c
 *
 * Created: 04.10.2021 12:40:59
 *  Author: thoander
 */ 

#include <avr/io.h>
#include "usart.h"

void usart_tx(unsigned char data) {
	while (! (UCSR0A & (1 << UDRE0))) {
		// wait for buffer to empty
	}
	// Place data in buffer
	UDR0 = data;
}

unsigned char usart_rx(void) {
	while(!(UCSR0A & (1 << RXC0))) {
		// Wait for data to be received
	}
	return UDR0;
}

void usart_init(unsigned int ubrr) {
	// Set baud rate
	UBRR0H = ubrr>>8;
	UBRR0L = ubrr;
	
	// Enable rx and tx
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	// Set frame format: 8data 2stop bit
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
	
	// Use printf for serial communication
	fdevopen(usart_tx, usart_rx);
	
}