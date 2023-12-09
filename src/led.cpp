//----------------------------------------------------------------------//
// Author: Brandon John Lim Yung Chen, Juan Sebastian Gultom, Mikha Kristofer, Axel Mahadriyana Ukar
// Date: December 12, 2023
// Assignment:     Class Project
//
// Description:  Setup the LEDs which will lit up randomly where the player will need to press button to the lit up LED accordingly
//----------------------------------------------------------------------//

#include <avr/io.h> // Includes all of the SFR macros
#include <util/delay.h> // Library for time-delay
#include "timer.h"

// Initialize the LED buttons to be set as outputs
void initLED(){
    // ---------------------------------------------------------------- //
    //      Define the ports of the LED on the Arduino ATMEGA 2560
    // ---------------------------------------------------------------- //
    // DDR[x] where DDR refers to Data Definition Register which controls the data direction for the pins on port [x]
    // [x] refers to a port where each port supposedly has eight pins
    // |= is a bitwise OR operator so to ensure the specified pin of a port will be 1 (output)
    // In other words, setting individual bits in a register without affecting the other bits
    // 1 is a reference bit
    // ----------------------------------------------------------------
    // DD[x][n] where DD refers to Data Direction which determines whether a pin is configured as an input or output
    // [x] refers to the section of a pin
    // [n] refers to the labeled number of a pin
    // (1 << DD[x][n]) is a bitwise shift operation
    // ----------------------------------------------------------------
    // Set the following pins as output
    DDRG |= (1 << DDG5); // Pin 4
    DDRE |= (1 << DDE3); // Pin 5
    DDRH |= (1 << DDH3) | (1 << DDH4) | (1 << DDH5) | (1 << DDH6); // Pin 6, pin 7, pin 8, and pin 9
}

// Turn ON a random LED button
void ledOn(int randomLed) {

    // PORT[x] refers to a specific port on the microcontroller
    // 1 << P[x][n] specifies the pin to be manipulated
    // |= (1 << P[x][n) is the operation for assigning a zero value (input) for the pin
    // in other words, turning ON the led

    if (randomLed == 1)
    { 
        PORTG |= (1 << PG5); // Turn ON LED from pin 4

    } else if (randomLed == 2)
    {
        PORTE |= (1 << PE3); // Turn ON LED from pin 5

    } else if (randomLed == 3)
    {
        PORTH |= (1 << PH3); // Turn ON LED from pin 6

    } else if (randomLed == 4)
    {
        PORTH |= (1 << PH4); // Turn ON LED from pin 7

    } else if (randomLed == 5)
    {
        PORTH |= (1 << PH5); // Turn ON LED from pin 8

    } else if (randomLed == 6)
    {
        PORTH |= (1 << PH6); // Turn ON LED from pin 9 
    }
}

// Turn OFF a random LED button
void ledOff(int randomLed) {

    // PORT[x] refers to a specific port on the microcontroller
    // 1 << P[x][n] specifies the pin to be manipulated
    // &= ~(1 << P[x][n) is the operation for assigning a zero value (input) for the pin
    // in other words, turning OFF the led

    if (randomLed == 1)
    {
        PORTG &= ~(1 << PG5); // Turn OFF LED from pin 4

    } else if (randomLed == 2)
    {
        PORTE &= ~(1 << PE3); // Turn OFF LED from pin 5

    } else if (randomLed == 3)
    {
        PORTH &= ~(1 << PH3); // Turn OFF LED from pin 6

    } else if (randomLed == 4)
    {
        PORTH &= ~(1 << PH4); // Turn OFF LED from pin 7

    } else if (randomLed == 5)
    {
        PORTH &= ~(1 << PH5); // Turn OFF LED from pin 8

    } else if (randomLed == 6)
    {
        PORTH &= ~(1 << PH6); // Turn OFF LED from pin 9 
    }
}

// Turn ON the LED buttons all at once
void ledOnAll() {

    PORTG |= (1 << PG5); // Turn on LED from pin 4
    PORTE |= (1 << PE3); // Turn on LED from pin 5
    PORTH |= (1 << PH3) | (1 << PH4) | (1 << PH5) | (1 << PH6); // Turn on LED from pin 6, pin 7, pin 8 and pin 9
}

// Turn OFF the LED buttons all at once
void ledOffAll() {

    PORTG &= ~(1 << PG5); // Turn OFF LED from pin 4
    PORTE &= ~(1 << PE3); // Turn OFF LED from pin 5
    PORTH &= ~((1 << PH3) | (1 << PH4) | (1 << PH5) | (1 << PH6)); // Turn OFF LED from pin 6, pin 7, pin 8, and pin 9
}

// Turn ON and OFF (blink) one of the specified button LED passed in the argument along with its time interval
void blink(int randomLed, int blinkTime) {

    ledOn(randomLed); // Turn ON a random LED button

    delayMs(blinkTime);

    ledOff(randomLed); // Turn OFF a random LED button

    delayMs(blinkTime);
}

// Turn ON and OFF (blink) all the button LEDs for a certain period of time
void blinkAllLED(int blinkTime) {

    ledOnAll(); // Turn ON all the LED buttons

    delayMs(blinkTime); // Delay the LED button blink by a certain amount of time in milliseconds

    ledOffAll(); // Turn OFF all the LED buttons

    delayMs(blinkTime); // Delay before the next LED button blink by a certain amount of time in milliseconds
}

// Reflex-Training Mode 1
void spin(int speed) {
    blink(1, speed);
    blink(2, speed);
    blink(3, speed);
    blink(4, speed);
    blink(5, speed);
    blink(5, speed);
}

// Reflex-Training Mode 2
void boomerang(int speed) {
    blink(1, speed);
    blink(2, speed);
    blink(3, speed);
    blink(4, speed);
    blink(5, speed);
    blink(6, speed);
    blink(5, speed);
    blink(4, speed);
    blink(3, speed);
    blink(2, speed);
    blink(1, speed);
}

// Read in the state value (based on HIGH or LOW) of all LED buttons and store each boolean state in a corresponding variable
bool readLEDState(int ledState) {

    if(ledState == 1)
    {
        // Read the value of pin 4
        return (PING & (1 << PING5)) != 0; // Return "true" or "false"
    
    } else if(ledState == 2)
    {
        // Read the value of pin 5
        return (PINE & (1 << PINE3)) != 0; // Return "true" or "false"
    
    } else if(ledState == 3)
    {
        // Read the value of pin 6
        return (PINH & (1 << PINH3)) != 0; // Return "true" or "false"

    } else if(ledState == 4)
    {
        // Read the value of pin 7
        return (PINH & (1 << PINH4)) != 0; // Return "true" or "false"

    } else if(ledState == 5)
    {
        // Read the value of pin 8
        return (PINH & (1 << PINH5)) != 0; // Return "true" or "false"
    
    } else if(ledState == 6)
    {
        // Read the value of pin 9
        return (PINH & (1 << PINH6)) != 0; // Return "true" or "false"
    }
}

// ----------------------------------------------------------------

// Delay the LED switch interval by a delayFactor upon the pushed button
void delayLoop(int delayFactor)
{
  // Delay can be increased by increasing the delayFactor thus prolonging the loop counter
    for (int i = 0; i < delayFactor; i++)
    {
      // Set a constant delay in milliseconds
        _delay_ms(100);
    }
}

// Initialize the variables for initial state
// flagLed is a control variable to light the LEDs back and forth from outwards to inwards and vice versa
int i = 0;
int flagLed = 0;

// runLED which returns void and takes in an unsigned int parameter called led
void runLED(unsigned int delay) {

    // Blink LEDs inwards
    if (flagLed == 0) {

        if (i > 3) {
            flagLed = 1;
        }
        i++;
    }
    // Blink LEDs outwards
    if (flagLed == 1) {
        if (i == 4) {
            i--;
        }
        i--;

        if (i == 0) {
            flagLed = 0;
        }
    }
    // Delay between LED blink
    delayLoop(delay);
}