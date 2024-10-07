#include "buttons.h"

volatile int pcint1PinLow = 0;
volatile bool timeToCheckGameStatus = false;
unsigned long lastInterruptTime = 0; // Variable to store the last interrupt time
const unsigned long debounceDelay = 50; // 50ms debounce time

void initButtonsAndButtonInterrupts(void)
{
    // Set pins A0-A3 (14-17) to use INPUT_PULLUP mode
    for (int i = A0; i <= A3; i++) {
        pinMode(i, INPUT_PULLUP);
    }

    // Activate PCINT1 (Port C), other ports disabled
    PCICR |= (1 << PCIE1); // Enable PCINT1

    // Enable PCINT14-17 (pins A0-A3)
    PCMSK1 = B00001111; // 0x0F; Enable pins A0, A1, A2, A3

    Serial.begin(9600); // Start serial communication at 9600 bps
    interrupts(); // Enable interrupts
}

ISR(PCINT1_vect) {
    unsigned long currentTime = millis(); // Get current time

    // Check if debounce delay has passed since the last valid interrupt
    if (currentTime - lastInterruptTime > debounceDelay) {
        for (int i = A0; i <= A3; i++) {
            // Read current pin state
            byte pinState = digitalRead(i);
        
            if (pinState == LOW) {
                // If pin is LOW, store it
                pcint1PinLow = i;

                Serial.print("PCINT1 interrupt on pin (HIGH to LOW) = ");
                Serial.println(pcint1PinLow);

                // Set flag for game status check
                timeToCheckGameStatus = true;

                // Update last interrupt time
                lastInterruptTime = currentTime;

                break; // Stop when the first LOW pin is found
            }
        }
        pcint1PinLow = 0; // Reset value to handle the next interrupt
    }
}


