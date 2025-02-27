#include "timer.h"
#include <Arduino.h>

void initializeTimer() {
    TCCR1A = 0;            // Nollataan rekisteri
    TCCR1B = 0b00001101;   // CTC-tila ja prescaler
    OCR1A = 15624;         // Timer-arvo (tämä voi olla muuttuvaa, riippuen pelistä)
    TIMSK1 = 0b00000010;   // Enabloidaan vertailu keskeytykset
    interrupts();          // Enabloidaan globaalit keskeytykset
}
