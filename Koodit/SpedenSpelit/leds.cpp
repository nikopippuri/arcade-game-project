#include "leds.h"
#include <arduino.h>

volatile int viive = 500;
int ledi_valon_kesto = 500;

// Määritä pinnit ledeille

void initializeLeds() {
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
};

// Sytytä tietty ledi

void setLed(byte ledNumber) {
  clearAllLeds();
  
  if (ledNumber == 0) {
    digitalWrite(5, HIGH);
    delay(ledi_valon_kesto);
    clearAllLeds();
  }
  else if (ledNumber == 1){
    digitalWrite(4, HIGH);
    delay(ledi_valon_kesto);
    clearAllLeds();
  }
  else if (ledNumber == 2){
    digitalWrite(3, HIGH);
    delay(ledi_valon_kesto);
    clearAllLeds();
  }
  else if (ledNumber == 3){
    digitalWrite(2, HIGH);
    delay(ledi_valon_kesto);
    clearAllLeds();
  }
};

// Sammuta kaikki ledit

void clearAllLeds(void) {
  for(int i=2; i<=5; i++){
    digitalWrite(i, LOW);
  }
};


void setAllLedsOn(void) {
  for(int i=2; i<=5; i++){
    digitalWrite(i, HIGH);
  }
};

// TURHA VALOSHOW 1

void show1(void){
  clearAllLeds();   // 0
  delay(500);
  digitalWrite(2, HIGH); // 1
  delay(500);

  clearAllLeds();
  digitalWrite(3, HIGH); // 2
  delay(500);

  clearAllLeds();
  digitalWrite(2, HIGH); // 1
  digitalWrite(3, HIGH); // 2
  delay(500);

  clearAllLeds();
  digitalWrite(4, HIGH); // 4
  delay(500);

  clearAllLeds();
  digitalWrite(2, HIGH); // 1
  digitalWrite(4, HIGH); // 4
  delay(500);

  clearAllLeds();
  digitalWrite(3, HIGH); // 2
  digitalWrite(4, HIGH); // 4
  delay(500);

  clearAllLeds();
  digitalWrite(2, HIGH); // 1
  digitalWrite(3, HIGH); // 2
  digitalWrite(4, HIGH); // 4
  delay(500);

  clearAllLeds();
  digitalWrite(5, HIGH); // 8
  delay(500);

  clearAllLeds();
  digitalWrite(2, HIGH); // 1
  digitalWrite(5, HIGH); // 8
  delay(500);

  clearAllLeds();
  digitalWrite(3, HIGH); // 2
  digitalWrite(5, HIGH); // 8
  delay(500);

  clearAllLeds();
  digitalWrite(2, HIGH); // 1 
  digitalWrite(3, HIGH); // 2
  digitalWrite(5, HIGH); // 8
  delay(500);

  clearAllLeds();
  digitalWrite(4, HIGH); // 4
  digitalWrite(5, HIGH); // 8
  delay(500);

  clearAllLeds();
  digitalWrite(2, HIGH); // 1 
  digitalWrite(4, HIGH); // 4
  digitalWrite(5, HIGH); // 8
  delay(500);

  clearAllLeds();
  digitalWrite(2, HIGH); // 1 
  digitalWrite(4, HIGH); // 4
  digitalWrite(5, HIGH); // 8
  delay(500);

  clearAllLeds();
  digitalWrite(3, HIGH); // 2 
  digitalWrite(4, HIGH); // 4
  digitalWrite(5, HIGH); // 8
  delay(500);

  clearAllLeds();
  setAllLedsOn(); // kaikki palaa = 15
  delay(500);

};

// TURHA VALOSHOW 2

void show2(int rounds){	
  for (int i=0; i < rounds; i++)
    
    
  clearAllLeds();
  digitalWrite(5, HIGH); //
  delay(viive);

  clearAllLeds();
  digitalWrite(4, HIGH); //
  delay(viive); 

  clearAllLeds();
  digitalWrite(3, HIGH); //
  delay(viive);

  clearAllLeds();
  digitalWrite(2, HIGH); //
  delay(viive);
  
 if (viive > 50) {
            viive = viive - 50;
        }


};

