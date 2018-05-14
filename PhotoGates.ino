/*
	PhotoGate.cpp - Library for PhotoGate control.
	Created by Rahul Goyal, August 19, 2017.
	Released to Cal Poly Baja SAE. ;)
*/

#include <PhotoGate.h>

// Constants Declarations and Initializations (Change at will)
#define NUMGATES 2		// Number of photogates

// Don't use pins 0, 1, 13
#define CALIBBUTTON 3	// Calibration button port
#define RESETBUTTON 4	// Reset button port
#define STATSBUTTON 5	// Stats button port
#define RESETBUTLED 2	// Reset LED port

boolean isTriggered;

// Create photoGate Array
PhotoGate photoGate[NUMGATES];



void setup() {

	// Initialize photoGate Objects
	for (unsigned i = 0 ; i < NUMGATES ; ++i) {
		photoGate[i].init(A0 + i);
	}

	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		;	// Wait for serial port to connect. Needed for native USB port only.
	}

	// Set pin modes
	pinMode(CALIBBUTTON, INPUT_PULLUP);	// Calibration button
	pinMode(RESETBUTTON, INPUT_PULLUP);	// Reset button
	pinMode(STATSBUTTON, INPUT_PULLUP);	// Stats button
	pinMode(RESETBUTLED, OUTPUT);		// Reset LED

}



void loop() {

	if (digitalRead(CALIBBUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();

		// Reset all photogate calibrations
		Serial.println("Resetting all photogate calibrations...");
		for (unsigned i = 0; i < NUMGATES; ++i) {
			photoGate[i].resetCal();
		}
		Serial.println("All photogate calibrations reset!");
	}



	if (digitalRead(RESETBUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();

		// Reset all photogate times		
		Serial.println("Resetting all photogate times...");
		for (unsigned i = 0; i < NUMGATES; ++i) {
			photoGate[i].resetRun();
		}
		Serial.println("All photogate timers reset!");
	}



	if (digitalRead(STATSBUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();

		for (unsigned i = 0; i < NUMGATES; ++i) {
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

		for (unsigned i = 0; i < NUMGATES; ++i)  {
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

		// Add motivational code here for slow times.

	}



	isTriggered = false;

	for (unsigned i = 0; i < NUMGATES; ++i) {
		photoGate[i].updateAll();
		isTriggered = isTriggered || photoGate[i].getTime();
	}

	if (isTriggered) {
		digitalWrite(RESETBUTLED, HIGH);
	} else {
		digitalWrite(RESETBUTLED, LOW);
	}

}



double elapsedTime() {
	return (photoGate[1].getTime() - photoGate[0].getTime()) / 1000000.0;
}
