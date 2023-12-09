//----------------------------------------------------------------------//
// Author: Brandon John Lim Yung Chen, Juan Sebastian Gultom, Mikha Kristofer, Axel Mahadriyana Ukar
// Date: December 12, 2023
// Assignment:     Class Project
//
// Description:  Setup the lit up LED randomizer and output the player's performance results after finishing
//----------------------------------------------------------------------//

#include <Arduino.h>
#include "led.h"
#include "switch.h"
#include "random.h"

bool ledState1 = 0;
bool ledState2 = 0;
bool ledState3 = 0;
bool ledState4 = 0;
bool ledState5 = 0;
bool ledState6 = 0;

bool buttonState1;
bool buttonState2;
bool buttonState3;
bool buttonState4;
bool buttonState5;
bool buttonState6;

bool nextState;
bool wrongState = 0;
unsigned long startTime;
unsigned long finishTime;
const int playingTime = 1;  // Minute

int shoot;
int goal;
int wrong;
bool pressed = 0;
bool buttonState = 0;
bool playGame;
int randomLed;
int oldRandomLed;
const int blinkingTime = 1000;

// What the heck is this for?
void nothing() {}

// Check whether the player has initiated Reflex-Training button to begin training
bool keyPress() {
  
    buttonState1 = readButtonState(1);
    buttonState2 = readButtonState(2);
    buttonState3 = readButtonState(3);
    buttonState4 = readButtonState(4);
    buttonState5 = readButtonState(5);
    buttonState6 = readButtonState(6);

    if (buttonState1 == 0 || buttonState2 == 0 || buttonState3 == 0 || buttonState4 == 0 || buttonState5 == 0 || buttonState6 == 0) {
        pressed = 1;
    }
    return pressed;
}

// Randomize the lit up LED buttons upon starting the Flex-Training
void pickNewLED() {

    // Read the state of pins PA0 to PA5
    ledState1 = readLEDState(1);
    ledState2 = readLEDState(2);
    ledState3 = readLEDState(3);
    ledState4 = readLEDState(4);
    ledState5 = readLEDState(5);
    ledState6 = readLEDState(6);

    // Read the state of pins PA0 to PA5
    buttonState1 = readButtonState(1);
    buttonState2 = readButtonState(2);
    buttonState3 = readButtonState(3);
    buttonState4 = readButtonState(4);
    buttonState5 = readButtonState(5);
    buttonState6 = readButtonState(6);

    //
    if (buttonState1 == 1 && buttonState2 == 1 && buttonState3 == 1 && buttonState4 == 1 && buttonState5 == 1 && buttonState6 == 1 && buttonState == 0 && playGame == 1) {
        
        buttonState = 1;
        randomLed = random(1, 6);

        while (randomLed == oldRandomLed) {

            randomLed = random(1, 6);
        }
        
        oldRandomLed = randomLed;
        ledOn(randomLed);
        shoot++;
        Serial.println("random");
    }

    //
    if (ledState1 == 1 && buttonState1 == 0 || ledState2 == 1 && buttonState2 == 0 || ledState3 == 1 && buttonState3 == 0 || /*   */
        ledState4 == 1 && buttonState4 == 0 || ledState5 == 1 && buttonState5 == 0 || ledState6 == 1 && buttonState6 == 0) {
        
        ledOffAll();
        goal++;
        buttonState = 0;
        Serial.println("goalllllllllll");
    }

    //
    if ((ledState1 == 1 && buttonState2 == 0) || (ledState1 == 1 && buttonState3 == 0) || (ledState1 == 1 && buttonState4 == 0) || (ledState1 == 1 && buttonState5 == 0) || (ledState1 == 1 && buttonState6 == 0) || /*   */
        (ledState2 == 1 && buttonState1 == 0) || (ledState2 == 1 && buttonState3 == 0) || (ledState2 == 1 && buttonState4 == 0) || (ledState2 == 1 && buttonState5 == 0) || (ledState2 == 1 && buttonState6 == 0) || /*   */
        (ledState3 == 1 && buttonState1 == 0) || (ledState3 == 1 && buttonState2 == 0) || (ledState3 == 1 && buttonState4 == 0) || (ledState3 == 1 && buttonState5 == 0) || (ledState3 == 1 && buttonState6 == 0) || /*   */
        (ledState4 == 1 && buttonState1 == 0) || (ledState4 == 1 && buttonState2 == 0) || (ledState4 == 1 && buttonState3 == 0) || (ledState4 == 1 && buttonState5 == 0) || (ledState4 == 1 && buttonState6 == 0) || /*   */
        (ledState5 == 1 && buttonState1 == 0) || (ledState5 == 1 && buttonState2 == 0) || (ledState5 == 1 && buttonState3 == 0) || (ledState5 == 1 && buttonState4 == 0) || (ledState5 == 1 && buttonState6 == 0) || /*   */
        (ledState6 == 1 && buttonState1 == 0) || (ledState6 == 1 && buttonState2 == 0) || (ledState6 == 1 && buttonState3 == 0) || (ledState6 == 1 && buttonState4 == 0) || (ledState6 == 1 && buttonState5 == 0)) {
        
        //ledOffAll();
        wrongState = 1;
        //buttonState = 0;
        //Serial.println("wrongPressed");
        ledOffAll();
        buttonState = 0;
    }
    //Serial.println(flag);
    //Serial.println("gggggggggg");
    if (wrongState == 1) {
        
        wrongState = 0;
        wrong++;
        Serial.println("wrong");
    }
    //Serial.println((finishTime - startTime) / 1000);
    if (((finishTime - startTime) / 1000) > 10) {
        
        // Turn OFF all LED buttons
        ledOffAll();


        float total = wrong + goal;
        float accuracy = (goal / total) * 100;
        float goalHelp = goal;
        float reactionTime = 60 / (total);
        float score;


        Serial.print(goal);
        Serial.print("\t");
        Serial.print(wrong);
        Serial.print("\t");
        Serial.print(accuracy);
        Serial.print("\t");
        Serial.println(reactionTime, 3);
        // Serial.print("\t");
        // Serial.println(reactionTime, 3);


        playGame = 0;
        buttonState = 0;


        boomerang(20);
        boomerang(20);


        pressed = 0;
    }
    //delay(5);
}