/*
	PhotoGate.cpp - Library for PhotoGate control.
	Created by Rahul Goyal, August 19, 2017.
	Released to Cal Poly Baja SAE. ;)
*/

/*

	*** COMPONENT DOCUMENTATION ***
	PhotoGate: Box containing photoresistor. See associated library.
	Buttons:
		Calibration: Reset each photogate's calibration numbers.
		Reset: Reset the run and each photogate's recorded time.
		Statistics: Output individual and overall photogate statistics.
	LEDs:
		Reset Button: Activates if any photogate has a recorded time.
		Status: Activates if its corresponding photogate is blocked.

	*** WIRING DOCUMENTATION ***
	Wire photogates in numerical order, starting at analog 0.
	Wire status LEDs in numerical order, starting at digital 8.
		See PhotoGate library.
	Define statements can adjust:
		Number of photogates.
		Pins of calibration, reset, and statistics buttons.

*/

#include <PhotoGate.h>

// Constants Declarations and Initializations (change at will)
#define NUM_GATES 2		// Number of photogates

// Don't use pins 0, 1, 13
#define CALIB_BUTTON 3	// Calibration button port
#define RESET_BUTTON 4	// Reset button port
#define STATS_BUTTON 5	// Stats button port
#define RESETBUT_LED 2	// Reset LED port

boolean isActivated;

// Create photoGate Array
PhotoGate photoGate[NUM_GATES];



void setup() {

	// Initialize photoGate Objects
	for (unsigned i = 0 ; i < NUM_GATES ; ++i) {
		photoGate[i].begin(A0 + i);
	}

	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		;	// Wait for serial port to connect. Needed for native USB port only.
	}

	// Set pin modes
	pinMode(CALIB_BUTTON, INPUT_PULLUP);	// Calibration button
	pinMode(RESET_BUTTON, INPUT_PULLUP);	// Reset button
	pinMode(STATS_BUTTON, INPUT_PULLUP);	// Stats button
	pinMode(RESETBUT_LED, OUTPUT);			// Reset LED

}



void loop() {

	if (digitalRead(CALIB_BUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();

		// Reset all photogate calibrations
		Serial.println("Resetting all photogate calibrations...");
		for (unsigned i = 0; i < NUM_GATES; ++i) {
			photoGate[i].resetCal();
		}
		Serial.println("All photogate calibrations reset!");
	}



	if (digitalRead(RESET_BUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();

		// Reset all photogate times		
		Serial.println("Resetting all photogate times...");
		for (unsigned i = 0; i < NUM_GATES; ++i) {
			photoGate[i].resetRun();
		}
		Serial.println("All photogate timers reset!");
	}



	if (digitalRead(STATS_BUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();

		for (unsigned i = 0; i < NUM_GATES; ++i) {
			Serial.print("PhotoGate ");
			Serial.print(i + 1);
			Serial.print(":");
			Serial.println();
			Serial.println("High: " + String(photoGate[i].getHigh()));
			Serial.println("Low: " + String(photoGate[i].getLow()));
			Serial.println("Mid: " + String(photoGate[i].getMid()));
			Serial.println("Light: " + String(photoGate[i].getLight()));
			Serial.println();
		}

		for (unsigned i = 0; i < NUM_GATES; ++i)  {
			Serial.print("PhotoGate ");
			Serial.print(i + 1);
			Serial.print("'s recorded system time is: ");
			Serial.print(photoGate[i].getTime());
			Serial.println();
		}

		Serial.println();
		Serial.print("The elapsed time is: ");
		Serial.print(String(elapsedTime(), 6));
		Serial.print(" seconds.");
		Serial.println();

		// Insert motivational messages here.

	}



	// Update photogate variables and update reset button led status
	isActivated = false;
	for (unsigned i = 0; i < NUM_GATES; ++i) {
		photoGate[i].updateAll();
		isActivated = isActivated || photoGate[i].getTime();
	}
	digitalWrite(RESETBUT_LED, isActivated);

}



double elapsedTime() {
	return (photoGate[1].getTime() - photoGate[0].getTime()) / 1000000.0;
}
