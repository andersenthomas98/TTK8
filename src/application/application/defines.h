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

/*
	Be aware that the application will not function as intended if the pins are not defined on the same port as they are now
*/

/******** Encoder left ********/
#define ENCA1 PORTD2 // (INT0) (Arduino Uno pin 2)
#define ENCB1 PORTD4 // (Arduino Uno pin 4)

/*************************/

/******** Encoder right ********/
#define ENCA2 PORTD3 // (INT1) (Arduino Uno pin 3)
#define ENCB2 PORTD7 // (Arduino Uno pin 7)
/*************************/

/******** PWM left(8-bit) *********/
#define MIN_PWM_DUTY_LEFT 135
#define PWM1 PD6 //OC0A // (Arduino Uno pin 6)

/**********************/

/******** PWM right(8-bit) *********/
#define MIN_PWM_DUTY_RIGHT 135
#define PWM2 PD5 //OC0B // (Arduino Uno pin 5)

/**********************/

/******** L298N control pins ********/
#define OUT1 PORTC0 // (Arduino Uno pin A0)
#define OUT2 PORTC1 // (Arduino Uno pin A1)
#define OUT3 PORTC2 // (A2)
#define OUT4 PORTC4 // (A3)
 

/************************************/

#endif /* DEFINES_H_ */