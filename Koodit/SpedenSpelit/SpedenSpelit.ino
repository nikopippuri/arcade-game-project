#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

byte randomNumbers[98];   // Taulukko arvottujen lukujen tallentamiseen
byte userNumbers[98];     // Taulukko pelaajan painamien lukujen tallentamiseen
int currentIndex = 0;     // Taulukon indeksi satunnaisluvuille
int buttonIndex = 0;      // Taulukon indeksi pelaajan painamille numeroille
int drawCount = 0;        // Arvontojen määrän laskuri pelin nopeuttamista varten
int timerSpeed = 15624;   // Timer-arvo
volatile int buttonNumber = -1;           // Talletetaan painettu nappi
volatile bool newTimerInterrupt = false;  // Timerin keskeytys
bool START = true;        // Pelin aloituksen odotus            
bool resetState = false;  // Resetoinnin tila
// Debounce kytkin värinän poisto
volatile unsigned long lastDebounceTime = 0;   // Edellisen painalluksen aikaleima
const unsigned long debounceDelay = 250;        // 200 ms viive
// Lopputuloksen seuranta
int OIKEAT = 0;           // Oikeiden vastausten laskuri
// int ENNATYS = 0;       // Ennätys
// Väliaikainen autokäynnistys ja pelitila
bool peliKaynnissa = false;  // Peli käynnissä -lippu
bool alku = true;             // Väliaikainen aloitus


void setup() {

    randomSeed(analogRead(5));          // Random() funktion korjaava alustusfunktio
    Serial.begin(9600);  // Käynnistä sarjaviestintä 9600 nopeudella
    Serial.println("Pelin alustus alkaa...");
    initializeTimer();                  // Timer 1 alustus
    initButtonsAndButtonInterrupts();   // Painikkeiden määritys ja keskeytykset
    initializeLeds();                   // Ledien alustus
    initializeDisplay();                // Näyttöjen alustus           
    Serial.println("Peli alustettu!");
}

void loop() {

 if (START == true ) {  // Peli odottaa 
  setLed(0);
  setLed(1);
  setLed(2);
  setLed(3);
    if (buttonNumber >=0) {
         START = false;
       }

 }
  
   else if (buttonNumber >= 0 && !resetState) {  // Tarkistetaan onko nappia painettu ja ettei peli ole reset tilassa
        if (alku == true) {          
            Serial.println("Peli alkaa hetken kuluttua...");
            delay(2000);        
            startTheGame();
            alku = false;                                                

        } else if (buttonNumber >= 0 && buttonNumber < 4) {
            Serial.print("Painiketta ");
            Serial.print(buttonNumber);
            Serial.println(" painettu, tarkistetaan peli...");
            checkTheGame();
        }
       buttonNumber = -1;  // Nollataan napin numero jokaisen painalluksen jälkeen
    }

    if (peliKaynnissa && newTimerInterrupt) {       // Jos peli käynnissä ja keskeytys tullut
        byte randomValue = random(0, 4);            // Arpoo numeron 0,1,2,3 
        randomNumbers[currentIndex] = randomValue;  // Tallennetaan arvo taulukkoon
        Serial.print("Satunnaisluku arvottu: ");
        Serial.println(randomValue);
        setLed(randomValue);                        // Sytytetään vastaava LED

        currentIndex++;

        drawCount++;  // Nopeutuslaskuri
        if (drawCount == 10) {
            drawCount = 0;
            moreSpeed();  // Nopeutetaan peliä
        }
             newTimerInterrupt = false;  // Nollataan keskeytys
    }
      if (resetState) {
         digitalWrite(5, HIGH);
         delay(500);
         digitalWrite(5, LOW);
         delay(300);
         }

       if (buttonNumber == 0 && resetState){ 
          resetCountdown();
          delay(1000);
          reset();
          }
     
}

// FUNKTIOT & KESKEYTYKSET

void initializeTimer(void) {
    TCCR1A = 0;            // Nollataan rekisteri
    TCCR1B = 0b00001101;   // CTC-tila ja prescaler
    OCR1A = timerSpeed;    // Vertailuarvo
    TIMSK1 = 0b00000010;   // Enabloidaan vertailu keskeytykset
    interrupts();          // Enabloidaan globaalit keskeytykset
    Serial.println("Timer alustettu.");
}

void checkTheGame() {
    bool areSame = true;  // Oletus: pelaajan syöte ja arvotut luvut täsmäävät
    Serial.println("Tarkistetaan pelaajan syöte...");

    for (byte i = 0; i < buttonIndex; i++) {  // Käy läpi pelaajan arvaamat luvut
        if (userNumbers[i] != randomNumbers[i]) {
            areSame = false;  // Jos virhe, lopeta tarkistus
            break;
        }
    }

    if (areSame == false) {
        Serial.println("Väärä painike painettu. Peli päättyy.");
        stopTheGame();  // Peli päättyy
    } else {
        Serial.println("Oikea painike painettu & peli jatkuu");
        OIKEAT++;
        Serial.print("Pisteitä kasassa: ");
        Serial.println(OIKEAT);
        showResult(OIKEAT);
    }
}

void initializeGame() {
    Serial.println("Pelin alustus...");
    currentIndex = 0;  // Nollataan indeksit
    buttonIndex = 0;
    peliKaynnissa = true;
}

void startTheGame() {
    initializeGame();  // Pelin alustus
    Serial.println("Peli aloitettu!");
}

void stopTheGame() {
    peliKaynnissa = false;
    TCCR1B = 0;  // Pysäytetään timerin laskenta
    TIMSK1 &= ~(1 << OCR1A);   // Disabloidaan keskeytykset
    Serial.println("Peli pysäytetty.");
    Serial.print("LOPPUTULOS: ");
    Serial.println(OIKEAT);
    resetState = true;
   
  
 if (buttonNumber == 0) {   
   Serial.println("resetoidaan peli ");
   resetCountdown();
   delay(1000);
   reset();
 }

}
void reset() {

    OIKEAT = 0;
    currentIndex = 0;
    buttonIndex = 0;
    drawCount = 0;
    timerSpeed = 15624;  
    START = true;
    alku = true;
    resetState = false;
    buttonNumber = -1;
    initializeLeds();   // Resetoi LEDit
    initializeDisplay();
    initializeTimer();
}   

void resetCountdown() {
    delay(500);
   digitalWrite(2, HIGH);
   digitalWrite(3, HIGH);
   digitalWrite(4, HIGH);
   digitalWrite(5, HIGH);
   delay (500);
   digitalWrite(5, LOW);
    delay (500);
   digitalWrite(4, LOW);
    delay (500);
   digitalWrite(3, LOW);
    delay (500);
   digitalWrite(2, LOW);
}

void moreSpeed() {
    timerSpeed = timerSpeed * 0.9;  // Nopeutetaan timeria
    OCR1A = timerSpeed;  // Päivitetään timerin arvo
}

ISR(TIMER1_COMPA_vect) {
    newTimerInterrupt = true;  // Timerin keskeytys

}

ISR(PCINT1_vect) {
    unsigned long currentTime = millis();  // Tallenna nykyinen aika

    if ((currentTime - lastDebounceTime) > debounceDelay) {  // Tarkistetaan viive edellisen painalluksen ja nykyisen välillä
        for (int i = A0; i <= A3; i++) {
            byte pinState = digitalRead(i);
            if (pinState == LOW) {  // Jos nappi on painettu
                buttonNumber = i - A0;  // Talletetaan nappi
                userNumbers[buttonIndex++] = buttonNumber;  // Talletetaan pelaajan painallus

                Serial.print("Painettu nappi: ");
                Serial.println(buttonNumber);  // DEBUG

                lastDebounceTime = currentTime;  // Päivitetään viimeisin painallusaika
                break;
            }
        }
    }
}
