/*
 * usart.h
 *
 * Created: 04.10.2021 12:41:19
 *  Author: thoander
 */ 


#ifndef USART_H_
#define USART_H_

#define FOSC 16000000 // clock speed
#define BAUD 9600
#define UBRR ((FOSC / (BAUD * 16UL)) - 1)

void usart_tx(unsigned char data);

unsigned char usart_rx(void);

void usart_init(unsigned int ubrr);



#endif /* USART_H_ */