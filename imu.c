/*
 * imu.c
 *
 * Created: 23.02.2013 15:07:21
 *  Author: OliverS
 *
 * $Id$
*/ 

#include "global.h"
#include "sensors.h"
#include <stdlib.h>
#include <avr/pgmspace.h>

int16_t ANGLE[3];
int16_t ACC_ANGLE[2];
int16_t GYR_ANGLE[3];

static const uint8_t convtab[] PROGMEM =
{
	0, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	19, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 31, 32, 33, 34, 35,
	36, 37, 38, 39, 41, 42, 43, 44, 46, 47, 48, 50, 51, 53, 54, 56, 57,
	59, 61, 63, 65, 67, 69, 72, 76, 80, 90,
};

static int8_t GetConv(int16_t input)
{
	uint8_t index = abs(input) >> 1;
	uint8_t conv = pgm_read_byte(&convtab[index]);
	if (input < 0)
		conv = -conv;
	return conv;
}

static void calcGyroAngles()
{
	static uint16_t lastCall;
	uint16_t dt = ticks() - lastCall;
	
	GYR_ANGLE[XAXIS] += GYRO[XAXIS] * dt;
	GYR_ANGLE[YAXIS] += GYRO[YAXIS] * dt;
	GYR_ANGLE[ZAXIS] += GYRO[ZAXIS] * dt;
}

static void calcAccAngles()
{
	ACC_ANGLE[XAXIS] = GetConv(ACC[XAXIS]);
	ACC_ANGLE[YAXIS] = GetConv(ACC[YAXIS]);
	if (ACC[ZAXIS] < 0)
	{
		if (ACC_ANGLE[XAXIS] < 0)
			ACC_ANGLE[XAXIS] = -180 - ACC_ANGLE[XAXIS];
		else
			ACC_ANGLE[XAXIS] = 180 - ACC_ANGLE[XAXIS];
		
		if (ACC_ANGLE[YAXIS] < 0)
			ACC_ANGLE[YAXIS] = -180 - ACC_ANGLE[YAXIS];
		else
			ACC_ANGLE[YAXIS] = 180 - ACC_ANGLE[YAXIS];
	}
}

#define ALPHA		3L
#define MAXALPHA	128L

static void calcComplementaryFilter()
{
	static uint16_t lastCall;
	uint16_t dt = ticks() - lastCall;
	int32_t r;
	
	r = (MAXALPHA - ALPHA) * (ANGLE[XAXIS] + (int32_t)GYRO[XAXIS] * dt / 20000L) + ALPHA * ACC_ANGLE[XAXIS];
	ANGLE[XAXIS] = r >> 7;
	
	r = (MAXALPHA - ALPHA) * (ANGLE[YAXIS] + (int32_t)GYRO[YAXIS] * dt / 20000L) + ALPHA * ACC_ANGLE[YAXIS];
	ANGLE[YAXIS] = r >> 7;
	
	lastCall += dt;
}

void imuCalculate()
{
	calcAccAngles();
	//calcGyroAngles();
	calcComplementaryFilter();
}