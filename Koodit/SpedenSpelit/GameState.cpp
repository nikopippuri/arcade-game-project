#include "GameState.h"
#include "EEPROM.h"
#include "display.h"
#include "leds.h"
#include "buttons.h"
#include "timer.h"

// Resetoi pelin tila
void GameState::reset() {
    correctAnswers = 0;
    currentIndex = 0;
    buttonIndex = 0;
    drawCount = 0;
    timerSpeed = 15624;
    isGameWaitingToStart = true;
    isGameStartDelayed = true;
    isGameRunning = false;
    buttonNumber = -1;
    initializeLeds();
    initializeDisplay();
    initializeTimer();
}

// Aloita peli
void GameState::start() {
    reset();  // Alustetaan peli
    isGameRunning = true;  // Nyt peli käynnistyy oikein
    isGameWaitingToStart = false;
    Serial.println("Peli aloitettu!");
}

// Pysäytä peli
void GameState::stop() {
    isGameRunning = false;
    TCCR1B = 0;  // Pysäytetään timerin laskenta
    TIMSK1 &= ~(1 << OCR1A);  // Disabloidaan keskeytykset
    Serial.println("Peli pysäytetty.");
    Serial.print("LOPPUTULOS: ");
    Serial.println(correctAnswers);

    if (correctAnswers > highScore) {
        EEPROM.write(0, correctAnswers);  // Päivitetään ennätys
    }

    isGameWaitingToStart = true;
}

// Tarkista pelaajan syöte
void GameState::checkPlayerInput() {
    bool isCorrect = true;

    for (byte i = 0; i < buttonIndex; i++) {
        if (userNumbers[i] != randomNumbers[i]) {
            isCorrect = false;
            break;
        }
    }

    if (isCorrect) {
        Serial.println("Oikea painike painettu & peli jatkuu");
        correctAnswers++;
        Serial.print("Pisteitä kasassa: ");
        Serial.println(correctAnswers);
        showResult(correctAnswers);
    } else {
        Serial.println("Väärä painike painettu. Peli päättyy.");
        stop();  // Lopeta peli
    }
}

// Käsittele pelin vuoro
void GameState::handleGameTurn() {
    byte randomValue = random(0, 4);
    randomNumbers[currentIndex] = randomValue;
    Serial.print("Satunnaisluku arvottu: ");
    Serial.println(randomValue);
    setLed(randomValue);

    currentIndex++;
    drawCount++;

    if (drawCount == 10) {
        drawCount = 0;
        moreSpeed();
    }
}

// Lisää pelin nopeutta
void GameState::moreSpeed() {
    timerSpeed = timerSpeed * 0.9;
    OCR1A = timerSpeed;
}
