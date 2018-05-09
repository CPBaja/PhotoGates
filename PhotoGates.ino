/*
	PhotoGate.cpp - Library for PhotoGate control.
	Created by Rahul Goyal, August 19, 2017.
	Released to Cal Poly Baja SAE. ;)
*/

#include <PhotoGate.h>

// Constants Declarations and Initializations (Change at will.)
#define NUMGATES 2	// Number of photogates

// DON'T USE PIN 13!!!
#define CALIBBUTTON 2
#define RESETBUTTON 3
#define STATSBUTTON 4
#define RESETBUTLED 5

boolean isTriggered;

// Create photoGate Array
PhotoGate photoGate[NUMGATES];



void setup() {

	// Initialize photoGate Objects
	for (unsigned i = 0 ; i < NUMGATES ; ++i) {
		photoGate[i].init(A0 + i, CALIBBUTTON);
	}
	
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		;	// Wait for serial port to connect. Needed for native USB port only.
	}



	// Calibration button
	pinMode(CALIBBUTTON, INPUT_PULLUP);
	
	// Reset button
	pinMode(RESETBUTTON, INPUT_PULLUP);

	// Statistics button
	pinMode(STATSBUTTON, INPUT_PULLUP);

	// Reset Button LED
	pinMode(RESETBUTLED, OUTPUT);
	digitalWrite(RESETBUTLED, LOW);

}



void loop() {

	if (digitalRead(CALIBBUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();

		// Reset all photogate calibrations
		Serial.println("Resetting all photogate calibrations...");
		for (int i = 0; i < NUMGATES; i++) {
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
		for (int i = 0; i < NUMGATES; i++) {
			photoGate[i].resetRun();
		}
		Serial.println("All photogate timers reset!");
	}

	

	if (digitalRead(STATSBUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();
		
		for (int i = 0; i < NUMGATES; i++)  {
			Serial.print("PhotoGate ");
			Serial.print(i + 1);
			Serial.print("'s recorded system time is: ");
			Serial.print(photoGate[i].getTime());
			Serial.println();
		}

		Serial.print("The elapsed time is: ");
		Serial.print(photoGate[1].getTime() - photoGate[0].getTime());
		Serial.print(" microseconds.")
		Serial.println();

		// Add motivational code here for slow times.
	}



	isTriggered = false;

	for (int i = 0; i < NUMGATES; i++) {
		photoGate[i].updateAll();
		isTriggered = isTriggered || photoGate[i].getTime();
	}

	if (isTriggered) {
		digitalWrite(RESETBUTLED, HIGH);
	} else {
		digitalWrite(RESETBUTLED, LOW);
	}

}
