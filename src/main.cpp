//----------------------------------------------------------------------//
// Author: Brandon John Lim Yung Chen, Juan Sebastian Gultom, Mikha Kristofer, Axel Mahadriyana Ukar
// Date: December 12, 2023
// Assignment:     Class Project
//
// Description:  Main execution file
//----------------------------------------------------------------------//

#include <Arduino.h> // Library for serial printing or debuggin
#include <avr/io.h>
#include <avr/interrupt.h> // Library containing all possible interrupts across all AVR micro-controller (Preprocessor directive for interrupt)
#include "led.h"
#include "switch.h"
#include "random.h"
#include "timer.h"


/*
 * Define a set of states that can be used in the state machine using an enum.
 */
typedef enum stateType_enum {
wait_press, debounce_press,
wait_release, debounce_release
} stateType;

// Initialize state
// volatile is used since the state value changes outside the control of the code
volatile stateType state = wait_press;

unsigned int delayFactor = 1; // Set initial delay factor

int main()
{
  // Initialize serial communication between the Arduino board and a connected computer or another device
  // 9600 baud rate is set as a default option
  // Enables the usage of serial-related functions
  Serial.begin(9600);

  // The IoT lab code uses this baud rate, need to know reason why
  // Serial.begin(115200);

  	// Enable global interrupt for the ISR to run
	// AVR's global Interrupts Enable bit (I) must be set in the MCU 
	// control register SREG. This allows the AVR's core to process interrupts 
	// via ISRs when set and prevents them from running when cleared. It 
	// defaults to being cleared on power up, so we need to set it
	sei();

	// Initialize the LEDs and the switches
	initLED();
	initSwitchPAn();

	// Loop the program infinitely
	while(1)
	{
		// Set the delay factor back to 1 if the switch is not pressed
		delayFactor = 1;

		// True only if the switch is pressed, or in other words a low level state (polling)
		if( !(PINA & (1 << PA0)) )
		{
		// Serial.print("Switch is pressed!");
		// Serial.flush();
		delayFactor = 10; // LEDs will change with a rate of 1/10th of the default delay factor
		}
		// Calls the function related to the LEDs
		runLED(delayFactor);

		//-----------------------------------------------------

		// Idle Reflex-Training Game Mode
		if (keyPress() == 0 && playGame == 0) {

			// Begin time counter to record the time of the player
			startTime = millis();
			//ledOnAll();
			blinkAllLED(500);

		// Start Reflex-Training Game Mode
		} else if (keyPress() == 1 && playGame == 0) {

			//ledOffAll();
			//blinkAll(200);
			//delay(1000);
			startTime = millis();
			playGame = 1;
			shoot = 0;
			goal = 0;
			wrong = 0;
		}
		if (playGame == 1) {
			pickNewLED();
		}
		finishTime = millis();

		// Switch case for handling debounce
		switch(state) {
			case wait_press:
				break;
			case debounce_press:
				delayMs(1);
				state = wait_release;
				break;
			case wait_release:
				break;
			case debounce_release:
				delayMs(1);
				state = wait_press;
				break;
		}
	}
	return 0;
}

/* Implement a Pin Change Interrupt which handles the switch being
* pressed and released. When the switch is pressed and released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/

// Hardware Interrupts is used
// The interrupt occurs in response to a changing external event such as a pin going low

//  ISR checks every clock cycle and processes request as they come along.
// o Functions are kept in specific memory locations (listed in IVR Table in Datasheet).
// o Request Flags go up and interrupt the main function processing to excute ISR.
// o Main function is completely paused until ISR is complete and the flag goes back down.

ISR(PCINT0_vect){ // Need to add more conditions for the other switches or buttons used
  
	if(state == wait_press){
		state = debounce_press;
	}
	else if(state == wait_release){
		state = debounce_release;
	}
}

//--------------------------------------------

void setup() {

  randomSeed(analogRead(A3)); // What the hell is this for?
}