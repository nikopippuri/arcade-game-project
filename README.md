# Speden Spelit Arduino-game

## Project Overview

In this project, we are recreating the classic Finnish reaction game from the TV show **"Speden Spelit."** This nostalgic game tests players' reaction times and memory by lighting up an LED in a random sequence. Players must then press the corresponding button to match the light.

As gameplay progresses, the challenge intensifies with increasing speed, making it harder to keep up and score points. The current score is displayed on 7-segment displays, providing real-time feedback on performance.

This project is part of our school microcontroller course, where we apply our knowledge in a hands-on manner. The key components include buttons, LEDs, 7-segment displays, and game logic, all seamlessly controlled by an Arduino microcontroller. 

Through this project, we have learned about integrating hardware and software while developing our programming skills.

## Table of Contents
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Setup](#setup)
- [Circuit Diagrams](#circuit-diagrams)
- [Flowcharts](#flowcharts)
- [Authors](#authors)
- [License](#licence)

## Features

- **4 Buttons**: For user controls.
- **4 LED Lights**: Lights to indicate the next button to press.
- **7-Segment Displays**: To show the current score and/or high score.
- **Interrupt-Driven Logic**: Buttons and timers utilize interrupts.
- **Difficulty Change**: The speed of LEDs increases as the game progresses.

## Hardware Requirements
To replicate this project, you will need the following components:

- 1 x Arduino (Uno or compatible)
- 4 x Push Buttons
- 4 x LEDs
- 2 x 74HC595 Serial-to-Parallel Shift Registers
- 2 x 7-Segment Displays
- Resistors and wires
- Breadboard

## Software Requirements

- Arduino IDE
- Tinkercad

## Setup
Instructions for setting up and preparing project for use:

1. Clone the repository:
    ```bash
    git clone https://github.com/nikopippuri/speden-spelit-r2.git
    ```
2. Download project files into your Arduino IDE -programming environment.
3. Correctly plug in your Arduino and upload the code into the device.

## How to Play (Game Instructions)
Press any button to start the game.
The LED lights will turn on in a random order, and you need to press the corresponding button.
If you press the wrong button, the game ends.
If you answer correctly you get a point and the game gets faster.
The game saves alltime highscores to EEPROM memory and it will be displayed in the startup.

## Folder Structure

speden-spelit-r2/

├── Images/

│   ├── circuit_diagram.pdf         
│   ├── circuit_tinkercad.png      
│   └── flowchart.png              

├── Koodit/SpedenSpelit

│   ├── SpedenSpelit.h

│   ├── SpedenSpelit.ino

│   ├── buttons.cpp

│   ├── buttons.h       
│   ├── display.cpp 

│   ├── display.h          
│   ├── leds.cpp 

│   └── leds.h   

└── README.md


## Circuit Diagrams

Here is the circuit diagram in Tinkercad:

![Circuit diagram in Tinkercad](Images/circuit_tinkercad.png)

You can also download a detailed circuit diagram in PDF format [from this link](Images/circuit_diagram.pdf).

## Flowcharts
Here is the flowchart about gamelogic:

![Flowchart](Images/flowchart.png)

## Authors
-Iiro Toivari
-Jan-Markus Jaakola
-Mika Wallenius
-Niko Pippuri


## License

MIT License

Copyright (c) [2024] [See contributors in the "Authors" section]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

