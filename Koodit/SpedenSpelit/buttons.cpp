#include "buttons.h"




void initButtonsAndButtonInterrupts(void)
{
  // See requirements for this function from buttons.h

      // Asetetaan pinnit A0-A3 (14-17) käyttämään INPUT_PULLUP -tilaa
    for (int i = A0; i <= A3; i++) {
        pinMode(i, INPUT_PULLUP);
    }

    // Aktivoidaan PCINT1 (Portti C), muut portit disabloitu
    PCICR |= (1 << PCIE1); // PCINT1 käytössä

    // Enable PCINT14-17 (pinnit A0-A3)
    PCMSK1 = B00001111; // 0x0F; // Enable pins A0, A1, A2, A3

    Serial.begin(9600); // Sarjaviestintä alkaa nopeudella 9600 bps
    interrupts(); // Keskeytykset enabloidaan

}




