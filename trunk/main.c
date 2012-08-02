/*
 * main.c
 *
 * Created: 27.07.2012 09:03:19
 *  Author: OliverS
 *
 * $Id$
 */ 

#include "global.h"
#include "lcd.h"
#include "adc.h"
#include "rx.h"
#include "sensors.h"
#include "pwm.h"
#include "mixer.h"
#include "keyboard.h"
#include "menu.h"
#include <util/delay.h>

// for debugging
#include <stdlib.h>
#include <string.h>

uint8_t Armed;

void init()
{
	configInit();
	adcInit();
	rxInit(Config.RX_mode);
	mixerInit();
	pwmInit();
	lcdInit();
	keyboardInit();
	menuInit();
}

int main(void)
{
	char s[10];
	// setup hardware w/o interrupts
	setup();
	
	// enable interrupts
	sei();
	
	// init hardware
	init();

	lcdClear();	
		
	//_delay_ms(1000);  // wait for receiver start
	/*rxCalibrate();
	sensorsCalibateAcc();
	sensorsCalibateGyro();
	*/
	
	uint8_t r = 0;
	lcdClear();	

    while(1)
    {
		LED_TOGGLE;
		
		rxRead();
		sensorsReadGyro();
		sensorsReadAcc();
		//pwmWrite();
		lcdOutput();
		menuShow();
		
    }
}