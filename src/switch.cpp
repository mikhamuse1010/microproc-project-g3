//----------------------------------------------------------------------//
// Author: Brandon John Lim Yung Chen, Juan Sebastian Gultom, Mikha Kristofer, Axel Mahadriyana Ukar
// Date: December 12, 2023
// Assignment:     Class Project
//
// Description:  Setup the buttons for the player to press on upon the lit up LEDs
//----------------------------------------------------------------------//

#include <avr/io.h> // Includes all of the SFR macros

// Initializes pull-up resistor on the switches used and set them into input mode
void initSwitchPAn()
{
    // --------------------------------------------------
    // Initialize buttons for the Reflex-Training session
    // --------------------------------------------------
    
    // PA0 is pin #22 on the breadboard
    DDRA &= ~(1 << DDA0); // set DDA0 as the input
    PORTA |= (1 << PORTA0); // pull-up resistor initialized


    // PA1 is pin #23 on the breadboard
    DDRA &= ~(1 << DDA1); // set DDA1 as the input
    PORTA |= (1 << PORTA1); // pull-up resistor initialized


    // PA2 is pin #24 on the breadboard
    DDRA &= ~(1 << DDA2); // set DDA2 as the input
    PORTA |= (1 << PORTA2); // pull-up resistor initialized


    // PA3 is pin #25 on the breadboard
    DDRA &= ~(1 << DDA3); // set DDA3 as the input
    PORTA |= (1 << PORTA3); // pull-up resistor initialized


    // PA4 is pin #26 on the breadboard
    DDRA &= ~(1 << DDA4); // set DDA4 as the input
    PORTA |= (1 << PORTA4); // pull-up resistor initialized


    // PA5 is pin #27 on the breadboard
    DDRA &= ~(1 << DDA5); // set DDA5 as the input
    PORTA |= (1 << PORTA5); // pull-up resistor initialized

    // --------------------------------------------------
    // Initialize buttons for starting the training, begin a new training session, and end the training
    // --------------------------------------------------
    
    // PA5 is pin #28 on the breadboard (Start Training button)
    DDRA &= ~(1 << DDA6); // set DDA6 as the input
    PORTA |= (1 << PORTA6); // pull-up resistor initialized

    // PA5 is pin #29 on the breadboard (Begin New Training Session button)
    DDRA &= ~(1 << DDA7); // set DDA7 as the input
    PORTA |= (1 << PORTA7); // pull-up resistor initialized

    // PA5 is pin #30 on the breadboard (End Training Session button)
    DDRC &= ~(1 << DDC7); // set DDC7 as the input
    PORTC |= (1 << PORTC7); // pull-up resistor initialized
};

// Read in the state value of all Switch buttons and store each state in its corresponding variable
bool readButtonState(int buttonState) {

    if(buttonState == 1)
    {
        // Read the value of pin PA0
        return (PINA & (1 << PINA0)) != 0; // Return "true" or "false"
    
    } else if(buttonState == 2)
    {
        // Read the value of pin PA1
        return (PINA & (1 << PINA1)) != 0; // Return "true" or "false"
    
    } else if(buttonState == 3)
    {
        // Read the value of pin PA2
        return (PINA & (1 << PINA2)) != 0; // Return "true" or "false"

    } else if(buttonState == 4)
    {
        // Read the value of pin PA3
        return (PINA & (1 << PINA3)) != 0; // Return "true" or "false"

    } else if(buttonState == 5)
    {
        // Read the value of pin PA4
        return (PINA & (1 << PINA4)) != 0; // Return "true" or "false"
    
    } else if(buttonState == 6)
    {
        // Read the value of pin PA5
        return (PINA & (1 << PINA5)) != 0; // Return "true" or "false"
    }
}