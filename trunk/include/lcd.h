/*
 * lcd.h
 *
 * Created: 27.07.2012 13:13:11
 *  Author: OliverS
 *
 * $Id$
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/pgmspace.h>

extern prog_char lcdArrowUp[9];
extern prog_char lcdArrowDown[9];
extern prog_uchar lcdFont[][6];

void lcdInit();
void lcdClear();
void lcdSetPos(uint8_t line, uint8_t column);
void lcdWriteChar(char c);
void lcdWriteString(char *s);
void lcdWriteString_P(PGM_P s);
void lcdReverse(uint8_t reversed);
void lcdSetContrast(uint8_t contrast);
void lcdOutput();
void lcdWriteImage_P(PGM_P image, uint8_t width);
void lcdFill(uint8_t c, uint8_t width);

#endif /* LCD_H_ */