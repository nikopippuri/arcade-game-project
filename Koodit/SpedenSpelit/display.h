#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>


void initializeDisplay(void);

void writeByte(uint8_t number, bool last);


void writeHighAndLowNumber(uint8_t tens,uint8_t ones);


void showResult(byte result);

#endif
