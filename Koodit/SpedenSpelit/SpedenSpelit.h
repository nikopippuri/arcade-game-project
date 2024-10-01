#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

byte userNumbers[100]; //painetut napit talletetaan näppäinten keskeytyspalvelijassa
byte randomNumbers[100];  //Määritetään arvotut luvut taulukko   Arpominen tapahtuu Timer1:n keskeytyspalvelijassa
int currentIndex = 0; // Määritetään, että ensimmäinen arvottu luku tulee oikeaan paikkaan
int drawCount = 0; //Arvontojen määrän laskuri pelin nopeuttamista varten
int timerSpeed = 15624; 

/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
*/
void initializeTimer(){
   TCCR1A = 0;             // nollataan rekisterit
   TCCR1B = 0b00001101;    // CTC tila ja prescaler
   OCR1A  = timerSpeed;    // vertailuarvo
   TIMSK1 = 0b00000010;    // enabloidaan vertailu keskeytykset
  interrupts();            // enabloidaan globaalit keskeytykset
}


void initializeTimer();
// Intoduce TIMER1_COMPA_vect Interrupt SeRvice (ISR) function for timer. 
ISR(TIMER1_COMPA_vect) { //keskeytys tulee 1s välein timerilta ja keskeytyspalvelimella arvotaan luku randomNumbers alkioon ja vastaava ledi syttyy  

  byte randomValue =random(0,4);  //arpoo numeron 0,1,2,3 
  setLed(randomValue); //saatu random luvun tulisi sytyttää vastaava ledi 
  randomNumbers[currentIndex] = randomValue; //sijoittaa arvotun luvun taulukkoon 
  currentIndex++ ;  //kasvattaa taulukon indeksiä
  drawCount++ ;     // kasvattaa pelin nopeudenlaskuria 

     if(drawCount == 10) {    // jos laskuri 10, niin nopeutetaan timeria antamaan keskeytyksiä 10% nopeammin
       drawCount = 0;      // nollataan nopeuslaskuri
       moreSpeed();

   }
}

void moreSpeed() {
  timerSpeed = timerSpeed * 0.9;  // kertoo timerin arvon  -> koska timer saavuttaa uuden pienemmän arvon nopeammin vauhti kiihtyy 
  OCR1A  = timerSpeed; // Määritetään timerille uusin arvo 
}


/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
*/
void initializeGame();


/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/


void checkGame() {    // checkGame funktiota kutsutaan, kun tarkistetaan onko painettu oikeaa nappia. 

 bool areSame = true;   //oletetaan, että taulukot userNumbers ja randomNumbers täsmäävät

  for (byte i = 0; i < 100; i++) {    //aloitetaan tarkistamaan taulukoiden sisältöjä alkio kerrallaan

   if (userNumbers[i] != randomNumbers[i]) {
      areSame = false;    // jos eri eroavaisuuksia löytyy muutetaan areSame arvoksi false
      break;  } // keskeyttää silmukan, jos eroavaisuus löytyy, eikä käy turhaan kaikkia läpi
}
   if(!areSame) {   //tarkastetaan areSamen tila, jos muuttunut false arvoon ->  if lause toteutuu 
     stopTheGame();  //peli päättyy funktion kutsu 
 } 
   else {
    showResults();  // Jos taulukoiden alkiot ovat samat, peli jatkuu ja pelin tilanne näytetään showResults aliohjelmalla
}


/*
  void stopTheGame(void)
  keskeyttaa pelin ja nayttää tuloksen -> resetointi 
*/
void stopTheGame() {
    TCCR1B = 0;  //pysäyttää timerin laskennan
    TIMSK1 &= ~(1 << OCR1A);   //shift rekister left = disabloi keskeytykset.    
    void showResult();  // näyttää nykyisen pistetilanteen
    void show2()    // vilkuttaa valoja tms, mikä tarkoittaa uutta ennätystä.
        if longbuttonpress() == true {   // Jos nappia painetaan pitkään niin peli resetoidaan 
          void resetGame(); // tätä ei ole vielä olemassa 
          }
}
/*
  void resetGame(); {
Palataan ino tiedoston alkuun 

  }
*/


/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame() {

   InitializeGame();

#endif

