/*
 * defines.h
 *
 * Created: 04.10.2021 12:57:32
 *  Author: thoander
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_

#include <avr/io.h>

#define F_CPU 16000000UL

#define BUILTIN_LED PORTB5 // (Arduino Uno pin 13)
#define STATUS_LED PORTD1

/*
	Be aware that the application will not function as intended if the pins are not defined on the same port as they are now
	TODO:
		- Make it easier to switch port/pin layout
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
// Uses timer/counter0 on atmega328p

#define MIN_PWM_DUTY_LEFT 135
#define PWM1 PD6 //OC0A // (Arduino Uno pin 6)

/**********************/

/******** PWM right(8-bit) *********/
// Uses timer/counter0 on atmega328p

#define MIN_PWM_DUTY_RIGHT 135
#define PWM2 PD5 //OC0B // (Arduino Uno pin 5)

/**********************/

/******** L298N control pins ********/
#define OUT1 PORTC0 // (Arduino Uno pin A0)
#define OUT2 PORTC1 // (Arduino Uno pin A1)
#define OUT3 PORTC2 // (A2)
#define OUT4 PORTC3 // (A3)
 

/************************************/

#define LOW_PASS_WEIGHT 0.3

#define DEFAULT_TICKS_PER_ROT_LEFT 850
#define DEFAULT_TICKS_PER_ROT_RIGHT 850

#define ENABLE_ANTI_WINDUP 0




#define PI 3.14159265359
#define RAD2DEG 180.0 / PI
#define DEG2RAD PI / 180.0

#endif /* DEFINES_H_ */