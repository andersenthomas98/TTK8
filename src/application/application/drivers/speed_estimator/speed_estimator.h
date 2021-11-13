/*
 * speed_estimator.h
 *
 * Created: 07.10.2021 13:33:37
 *  Author: thoander
 */ 


#ifndef SPEED_ESTIMATOR_H_
#define SPEED_ESTIMATOR_H_

void speed_estimator_init(long ticks_per_rot_left, long ticks_per_rot_right);

float speed_estimator_left_rad_per_s();

float speed_estimator_right_rad_per_s();



#endif /* SPEED_ESTIMATOR_H_ */