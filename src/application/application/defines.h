/*
 * defines.h
 *
 * Created: 04.10.2021 12:57:32
 *  Author: thoander
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_

#include <avr/io.h>

#define BUILTIN_LED PORTB5

/******** Encoder left ********/
#define ENCA1 PORTD2 // (INT0)
#define ENCB1 PORTD6

/*************************/


/******** Encoder right ********/
#define ENCA2 PORTD3 // (INT1)
#define ENCB2 PORTD7
/*************************/

#endif /* DEFINES_H_ */