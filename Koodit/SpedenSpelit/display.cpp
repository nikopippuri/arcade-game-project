#include "display.h"

int latchPin = 8;  // Yhdistetään siirtorekisterin (74hc595) ST_CP (Storage Register Clock Input) Arduinon digital pinniin 8.
int dataPin = 11;  // Yhdistetään siirtorekisterin (74hc595) DS (Serial Data Output) Arduinon digital pinniin 11.
int clockPin = 12; // Yhdistetään siirtorekisterin (74hc595) SH_CP (Shift Register Clock Input) Arduinon digital pinniin 12

// Taulukko 0b-etuliite kertoo ohjelmalle että on tulossa 8-bittinen binääriluku
// 0b-etuliitteen jälkeen numerosarja tarkoittaa 7-segmentin segmenttejä DP-A-B-C-D-E-F-G
byte Taulukko[] = {
    0b01111110, // Esittää luvun 0  
    0b00110000, // Esittää luvun 1               
    0b01101101, // Esittää luvun 2  
    0b01111001, // Esittää luvun 3 
    0b00110011, // Esittää luvun 4 
    0b01011011, // Esittää luvun 5 
    0b01011111, // Esittää luvun 6 
    0b01110000, // Esittää luvun 7 
    0b01111111, // Esittää luvun 8 
    0b01111011  // Esittää luvun 9 
};

void initializeDisplay(void) // Alustetaan siirtorekisterin pinnit ulostulo-tilaan
{
pinMode (latchPin,OUTPUT); // Asetetaan latchPin Ulostulo-tilaan
pinMode (dataPin,OUTPUT);  // Asetetaan dataPin Ulostulo-tilaan
pinMode (clockPin,OUTPUT); // Asetetaan clockPin Ulostulo-tilaan
}

void writeByte(uint8_t number,bool last) // Hakee taulukosta kutsutun lukuarvon
{
if (number > 9) // Hyväksytään vain lukuarvot 0-9
{
return;
}

digitalWrite(latchPin,LOW);
digitalWrite(clockPin,LOW); // Valmistellaan tiedonsiirto asettamalla clock ja latchpin LOW-tilaan
shiftOut(dataPin,clockPin,LSBFIRST,Taulukko[number]); // Siirtää lukuarvon bitti bitiltä siirtorekisteriin.
if(last){ // Jos viimeinen tavu, asetetaan seuraavaksi latch HIGH-tilaan
digitalWrite(latchPin,HIGH); // Päivitetään luku näytölle asettamalla latch HIGH-tilaan.
}
}

void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
  writeByte(ones,false);
  writeByte(tens,true);
}

void showResult(byte number)
{
  uint8_t tens = number / 10;
  uint8_t ones = number % 10;
  writeHighAndLowNumber(tens,ones);
}

