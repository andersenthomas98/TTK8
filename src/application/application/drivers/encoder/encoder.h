/*
 * encoder.h
 *
 * Created: 04.10.2021 12:53:47
 *  Author: thoander
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

void encoder_init(void);

int encoder_read_tick(int encoder_pin);

int encoder_get_accumulated_ticks_left(void);

int encoder_get_accumulated_ticks_right(void);


#endif /* ENCODER_H_ */