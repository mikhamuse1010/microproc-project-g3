//----------------------------------------------------------------------//
// Author: Brandon John Lim Yung Chen, Juan Sebastian Gultom, Mikha Kristofer, Axel Mahadriyana Ukar
// Date: December 12, 2023
// Assignment:     Class Project
//
// Description:  Contains function prototypes to be implemented in led.cpp
//----------------------------------------------------------------------//

// Include this file once (header guards)
#ifndef LED_H
#define LED_H

//-------------------------------------------------------------------------------------------//
// Initialize the function prototypes to allow other files to know about them at compile time
//-------------------------------------------------------------------------------------------//

// Initialize the LED buttons to be set as outputs
void initLED();

// Turn ON a random LED button
void ledOn(int randomLed);

// Turn OFF a random LED button
void ledOff(int randomLed);

// Turn ON the LED buttons all at once
void ledOnAll();

// Turn OFF the LED buttons all at once
void ledOffAll();

// Turn ON and OFF (blink) one of the specified button LED passed in the argument along with its time interval
void blink(int randomLed, int blinkTime);

// Turn ON and OFF (blink) all the button LEDs for a certain period of time
void blinkAllLED(int blinkTime);

// Reflex-Training Mode 1
void spin(int speed);

// Reflex-Training Mode 2
void boomerang(int speed);

// Read in the state value (based on HIGH or LOW) of all LED buttons and store each boolean state in a corresponding variable
bool readLEDState(int ledState);

// ****************************************************************

// runLED which returns void and takes in an unsigned int parameter called led
void runLED(unsigned int led);

#endif