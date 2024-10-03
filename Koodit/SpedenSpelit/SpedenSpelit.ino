#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Muuttujien määrittelyt
byte randomNumbers[98];   // Taulukko arvottejuen lukujen tallentamiseen
byte userNumbers[98];     // Taulukko pelaajan painamien lukujen tallentamiseen
int currentIndex = 0;     // Taulukon indeksi
int drawCount = 0;        // Arvontojen määrän laskuri pelin nopeuttamista varten
int timerSpeed = 15624;   // Vahti
int OIKEAT = 0;           // DEBUG
bool peliKaynnissa = false; // DEBUG 


// Volatile-muuttujat keskeytyksiä varten
volatile int buttonNumber = -1;           // for buttonista tuleva keskeytys
volatile bool newTimerInterrupt = false;  // for timer interrupt handler

void setup() {
    Serial.begin(9600);  // Käynnistä sarjaviestintä 9600 nopeudella
    Serial.println("Pelin alustus alkaa..."); // DEBUG

    initializeTimer();                  // Timer 1 alustus

    initButtonsAndButtonInterrupts();   // Painikkeiden määritys ja keskeytykset

    initializeLeds();                   // Ledien alustus

    // initializeDisplays();            // Näyttöjen alustus

    Serial.println("Peli alustettu!");  // DEBUG

}

void loop() {

  while (peliKaynnissa) {
    // Tarkistetaan, mitään nappia painettu
    if (buttonNumber >= 0) {
        if (buttonNumber == 4) {
            Serial.println("Pelin aloitus nappia painettu, peli alkaa..."); // DEBUG käynnistysnappi
            startTheGame();                                             
        } else if (buttonNumber >= 0 && buttonNumber < 4) {
            Serial.print("Painiketta ");
            Serial.print(buttonNumber);
            Serial.println(" painettu, tarkistetaan peli...");
            checkTheGame();  // 
        }
        buttonNumber = -1;  // Nollataan napin numero
    }

    // Tarkistetaan, onko uusi keskeytys tullut Timer 1:ltä 
    if (newTimerInterrupt == true) {
        // Satunnaisluku ja vastaava LED syttyy
        byte randomValue = random(0, 4);            // arpoo numeron 0,1,2,3 
        randomNumbers[currentIndex] = randomValue;  // Sijoittaa arvotun luvun, randomNumbers taulukkoon

        Serial.print("Satunnaisluku arvottu: ");    // DEBUG
        Serial.println(randomValue);                // DEBUG
        setLed(randomValue);                        // DEBUG syttyykö valo
        currentIndex++;

        /* TAULUKOIDEN DEBUG

        for (int i = 0; i < 98; i++) {
        Serial.print("arvotut ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(randomNumbers[i]);
        Serial.print("arvaukset ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(userNumbers[i]);
        }

        */



        Serial.println(timerSpeed);

        drawCount++ ;     // kasvattaa pelin nopeudenlaskuria 
        if(drawCount == 10) {    // jos laskuri 10, niin nopeutetaan timeria antamaan keskeytyksiä 10% nopeammin
        drawCount = 0;      // nollataan nopeuslaskuri
        moreSpeed();

   }

        newTimerInterrupt = false;  // Nollataan keskeytyksen merkkibitti
    }
}
}

void initializeTimer(void) {
    // Alustetaan Timer 1
    TCCR1A = 0;            // Nollataan rekisteri
    TCCR1B = 0b00001101;   // CTC-tila ja prescaler
    OCR1A = timerSpeed;    // Vertailuarvo
    TIMSK1 = 0b00000010;   // Enabloidaan vertailu keskeytykset
    interrupts();          // Enabloidaan globaalit keskeytykset
    Serial.println("Timer alustettu.");
}

ISR(TIMER1_COMPA_vect) {
    // Asetetaan keskeytykseen true
    newTimerInterrupt = true;
}

void checkTheGame() {

  bool areSame = true;                                        //oletetaan, että taulukot userNumbers ja randomNumbers täsmäävät
   
    // Pelaajan syötteen tarkistus
    Serial.println("Tarkistetaan pelaajan syöte...");         // DEBUG

   for (byte i = 0; i < 100; i++) {    //aloitetaan tarkistamaan taulukoiden sisältöjä alkio kerrallaan

   if (userNumbers[i] != randomNumbers[i]) {
      areSame = false;    // jos eri eroavaisuuksia löytyy muutetaan areSame arvoksi false
      break;  } // keskeyttää silmukan, jos eroavaisuus löytyy, eikä käy turhaan kaikkia läpi
}
   if(!areSame) {   //tarkastetaan areSamen tila, jos muuttunut false arvoon ->  if lause toteutuu 
    Serial.println("Väärä painike painettu. Peli päättyy.");  // DEBUG
     stopTheGame();  //peli päättyy funktion kutsu 
 } 
   else {
    Serial.println("Oikea painike painettu & peli jatkuu");   // DEBUG
    showResult(OIKEAT);  // Jos taulukoiden alkiot ovat samat, peli jatkuu ja pelin tilanne näytetään showResults aliohjelmalla
}


    }


void initializeGame() {
    Serial.println("Pelin alustus...");
    currentIndex = 0;  // Nollataan taulukon indeksi
}

void startTheGame() {
    initializeGame();  // Pelin alustus
    Serial.println("Peli aloitettu!");
}

void stopTheGame() {
    TCCR1B = 0;  // Pysäytetään timerin laskenta
    TIMSK1 &= ~(1 << OCR1A);   // Disabloidaan keskeytykset
    Serial.println("Peli pysäytetty. Näytetään tulokset.");

    //  showResults();  // Kutsutaan funktiota, joka näyttää pelin tuloksen
    //  void show2();    // vilkuttaa valoja tms, mikä tarkoittaa uutta ennätystä.
}

void resetGame() {
    Serial.println("Peli resetoidaan...");
}

void moreSpeed() {
  timerSpeed = timerSpeed * 0.9;  // kertoo timerin arvon  -> koska timer saavuttaa uuden pienemmän arvon nopeammin vauhti kiihtyy 
  OCR1A  = timerSpeed; // Määritetään timerille uusin arvo 
}
