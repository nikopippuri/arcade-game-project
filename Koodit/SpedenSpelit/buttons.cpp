#include "buttons.h"


volatile int pcint1PinLow = 0;  
volatile bool timeToCheckGameStatus = false; 

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

ISR(PCINT1_vect) {

  for (int i = A0; i <= A3; i++) {
        // Luetaan nykyinen tila
        byte pinState = digitalRead(i);
        
        if (pinState == LOW) {
            // Jos pinni on LOW, talletetaan se
            pcint1PinLow = i;

            Serial.print("PCINT1-väylästä keskeytys pinnistä HIGH to LOW = ");
            Serial.println(pcint1PinLow);

            // LISÄÄ SAMALLA KYSEINEN LUKU painetut_nappulat[painetut_indeksi] taulukkoon??

          timeToCheckGameStatus = true;

            break; // Lopetetaan, kun ensimmäinen LOW-pinni on löydetty
        }

         pcint1PinLow = 0; // Nollataan arvo, jotta voidaan käsitellä seuraava keskeytys


}


