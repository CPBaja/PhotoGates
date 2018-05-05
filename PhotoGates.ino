#include <PhotoGate.h>

// Constants Declarations and Initializations (Change at will.)
const int NUMGATES = 2;  // Number of photogates set up

// DON'T USE PIN 13!!!
const int CALIBBUTTON = 8;
const int RESETBUTTON = 9;
const int STATSBUTTON = 10;

// const int RESETBUTLED = 12;



// Create photoGate Array (FIX LATER)
PhotoGate photoGate[] = {
	PhotoGate(A0, CALIBBUTTON, RESETBUTTON),
	PhotoGate(A1, CALIBBUTTON, RESETBUTTON),
	// PhotoGate(A2, CALIBBUTTON, RESETBUTTON),
	// PhotoGate(A3, CALIBBUTTON, RESETBUTTON),
	// PhotoGate(A4, CALIBBUTTON, RESETBUTTON),
	// PhotoGate(A5, CALIBBUTTON, RESETBUTTON)
};



void setup() {

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

}



void loop() {

	if (digitalRead(CALIBBUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();
		Serial.println("Resetting all photogate calibrations...");
		// Reset all photogate calibrations
		for (int i = 0; i < NUMGATES; i++) {
			photoGate[i].resetCal();
		}
		Serial.println("All photogate calibrations are reset!");
	}



	if (digitalRead(RESETBUTTON) == LOW) {    
		Serial.println();
		Serial.println();
		Serial.println();
		Serial.println("Resetting all photogate times...");
		// Reset all photogate times
		for (int i = 0; i < NUMGATES; i++) {
			photoGate[i].resetRun();
		}
		Serial.println("All photogate timers are reset!");
	}

	

	if (digitalRead(STATSBUTTON) == LOW) {
		Serial.println();
		Serial.println();
		Serial.println();
		for (int i = 0; i < NUMGATES; i++) {
			Serial.print("PhotoGate ");
			Serial.print(i + 1);
			Serial.print("'s TIME (in relative microseconds) is: ");
			Serial.print(photoGate[i].showStats());
			Serial.println();
		}
		Serial.print("The elapsed time (in microseconds) is: ");
		Serial.print(photoGate[1].showStats() - photoGate[0].showStats());
		Serial.println();
	}



	for (int i = 0; i < NUMGATES; i++) {
		photoGate[i].updateAll();
	}

}
