#ifndef GAMESTATE_H  // Suojataan tiedostoa moninkertaiselta sisällyttämiseltä
#define GAMESTATE_H

class GameState {
public:
    int randomNumbers[98];    // Arvottujen numeroiden taulukko
    int userNumbers[98];      // Pelaajan syöttämien numeroiden taulukko
    int currentIndex = 0;      // Satunnaislukujen indeksin seuranta
    int buttonIndex = 0;       // Pelaajan syöttämien numeroiden indeksin seuranta
    int correctAnswers = 0;    // Oikeiden vastausten laskuri
    int drawCount = 0;         // Arvontojen laskuri
    int timerSpeed = 15624;    // Ajastimen nopeus
    int highScore = 0;         // Ennätys

    bool isGameRunning = false;    // Peli käynnissä -lippu
    bool isGameWaitingToStart = true;   // Pelin odotustila
    bool isGameStartDelayed = true;    // Pelin aloitusviive

    unsigned long lastDebounceTime = 0;  // Debounce-aikaleima
    const unsigned long debounceDelay = 250;   // Viive debounce-toiminnolle

    int buttonNumber = -1;       // Tallentaa painetun napin
    volatile bool newTimerInterrupt = false;  // Timerin keskeytys

    // Metodit pelin tilan hallintaan
    void reset();
    void start();
    void stop();
    void checkPlayerInput();
    void handleGameTurn();
    void moreSpeed();
};

#endif  // GAMESTATE_H
