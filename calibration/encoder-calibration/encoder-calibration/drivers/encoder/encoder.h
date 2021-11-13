/*
 * encoder.h
 *
 * Created: 13.11.2021 14:15:43
 *  Author: thoander
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

void encoder_init(void);

int encoder_read_tick(int encoder_pin);

long encoder_get_accumulated_ticks_left(void);

long encoder_get_accumulated_ticks_right(void);


#endif /* ENCODER_H_ */