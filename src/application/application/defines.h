/*
 * defines.h
 *
 * Created: 04.10.2021 12:57:32
 *  Author: thoander
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_

#include <avr/io.h>

#define BUILTIN_LED PORTB5 // (Arduino Uno pin 13)

/******** Encoder left ********/
#define ENCA1 PORTD2 // (INT0) (Arduino Uno pin 2)
#define ENCB1 PORTD4 // (Arduino Uno pin 4)

/*************************/

/******** Encoder right ********/
#define ENCA2 PORTD3 // (INT1) (Arduino Uno pin 3)
#define ENCB2 PORTD7 // (Arduino Uno pin 7)
/*************************/

/******** PWM (8-bit) *********/
#define PWM1 PD6 //OC0A // (PD6)
#define PWM2 PD5 //OC0B // (PD5)



/**********************/

#endif /* DEFINES_H_ */