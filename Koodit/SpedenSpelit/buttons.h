#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void initButtonsAndButtonInterrupts(void);

// Intoduce PCINT1_vect Interrupt SeRvice (ISR) function for Pin Change Interrupt.
ISR(PCINT1_vect); 
#endif;
