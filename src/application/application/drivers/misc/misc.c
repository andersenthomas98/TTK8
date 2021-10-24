/*
 * misc.c
 *
 * Created: 23.10.2021 15:58:28
 *  Author: thoander
 */ 

#include "misc.h"

float abs(float val) {
	if (val < 0) {
		return val*(-1.0);
	}
	return val;
}