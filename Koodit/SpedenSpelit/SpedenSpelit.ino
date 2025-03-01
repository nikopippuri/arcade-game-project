#include "GameState.h"
#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "EEPROM.h"
#include "timer.h"

GameState gameState;  // Luodaan GameState-objekti

void setup() {
    randomSeed(analogRead(5));  // Alustetaan satunnaisluku
    Serial.begin(9600);         // Käynnistetään sarjaviestintä 9600 nopeudella

    gameState.highScore = EEPROM.read(0);  // Lue ennätys EEPROMista
    if (gameState.highScore == 255) {
        EEPROM.write(0, 0);  // Aseta ennätykseksi 0, jos ei ennätystä
    }

    Serial.print("Ennätys: ");
    Serial.println(gameState.highScore);

    Serial.println("Pelin alustus alkaa...");
    initializeTimer();
    initButtonsAndButtonInterrupts();
    initializeLeds();
    initializeDisplay();
    showResult(gameState.highScore);
    Serial.println("Peli alustettu!");
}

void loop() {
    if (gameState.isGameWaitingToStart) {
        showResult(gameState.highScore);
        setAllLedsOn();  // Sytytetään kaikki LEDit, peli odottaa aloitusta

        if (gameState.buttonNumber >= 0) {
            Serial.println("Aloituspainike painettu, peli alkaa!");
            gameState.isGameWaitingToStart = false;
            gameState.isGameStartDelayed = true;
        }
    } 
    else if (gameState.buttonNumber >= 0 && !gameState.isGameWaitingToStart) {
        if (gameState.isGameStartDelayed) {
            Serial.println("Peli alkaa hetken kuluttua...");
            delay(2000);
            gameState.start();  // Aloitetaan peli
            gameState.isGameStartDelayed = false;
        } else if (gameState.buttonNumber >= 0 && gameState.buttonNumber < 4) {
            gameState.checkPlayerInput();  // Tarkistetaan pelaajan syöte
        }
        gameState.buttonNumber = -1;
    }

    if (gameState.isGameRunning && gameState.newTimerInterrupt) {
        gameState.handleGameTurn();  // Käsitellään pelin vuoro
    }

    if (gameState.isGameWaitingToStart && gameState.buttonNumber == 0) {
        show1();
        delay(1000);
        gameState.reset();  // Resetoi peli
    }
}
