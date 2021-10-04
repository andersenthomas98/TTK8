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
#define ENCB1 PORTD6 // (Arduino Uno pin 6)

/*************************/

/******** Encoder right ********/
#define ENCA2 PORTD3 // (INT1) (Arduino Uno pin 3)
#define ENCB2 PORTD7 // (Arduino Uno pin 7)
/*************************/



#endif /* DEFINES_H_ */