#ifndef LEDS_H
#define LEDS_H
#include <arduino.h>

/*
  initializeLeds() subroutine intializes analog pins A2,A3,A4,A5
  to be used as outputs. Speden Spelit leds are connected to those
  pins.  
*/

volatile int viive = 500;
int ledi_valon_kesto = 500;

void initializeLeds() {
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
};

/*
  setLed(byte) sets correct led number given as 0,1,2 or 3
  led number 0 corresponds to led connected at Arduino pin A2
  led number 1 => Arduino pin A3
  led number 2 => Arduino pin A4
  led number 3 => Arduino pin A5
  
  parameters:
  byte ledNumber is 0,1,2 or 3


*/
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

/*
  clearAllLeds(void) subroutine clears all leds
*/
void clearAllLeds(void) {
  for(int i=2; i<=5; i++){
    digitalWrite(i, LOW);
  }
};

/*
  setAllLeds subroutine sets all leds
*/

// KAIKILLE OMAT VASTUKSET


void setAllLeds(void) {
  for(int i=2; i<=5; i++){
    digitalWrite(i, HIGH);
  }
};;

/*
  show1() subroutine shows numbers 0,1,...,15 as binary numbers
  waits a bit and repeats number "show"
*/
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
  setAllLeds(); // kaikki palaa = 15
  delay(500);

};

/*
  show2(int) subroutine shows leds 0,1,2,3,0,1,2,3,.... with increasing
  changing rate. And when top change speed has been reached

    Parameters:
  
  int rounds: This parameter determines how many times 0,1,2,3 sequence
              is shown. 
*/
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

#endif
