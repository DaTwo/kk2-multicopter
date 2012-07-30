/*
 * config.h
 *
 * Created: 30.07.2012 11:42:33
 *  Author: OliverS
 *
 * $Id$
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include "global.h"
#include "mixer.h"

typedef struct  
{
	uint8_t signature;
	uint16_t RX_zero[RX_CHANNELS];
	MixerModel Mixer;
} Config_t;

extern Config_t Config;

void configSave();
void configInit();


#endif /* CONFIG_H_ */