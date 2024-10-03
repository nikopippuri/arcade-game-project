#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H

#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Funktioprototyypit
void initializeTimer();                   // Timerin alustus
void initializeGame();                    // Pelin alustus
void startTheGame();                      // Pelin käynnistys
void checkTheGame(byte lastButtonPress);  // Tarkistetaan pelaajan syöte
void stopTheGame();                       // Pysäytetään peli
void resetTheGame();                      // Resetoidaan peli
void moreSpeed();                         // Pelinopeuden kasvatus

#endif
