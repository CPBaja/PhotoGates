/*
	PhotoGate.h - Library header for PhotoGate control.
	Created by Rahul Goyal, August 19, 2017.
	Released to Cal Poly Baja SAE. ;)
*/

#ifndef PhotoGate_h
#define PhotoGate_h

#include "Arduino.h"

class PhotoGate {

	public:
		// Constructors
		PhotoGate();
		void begin(int pin);

		// Reset high, low
		void resetCal();

		// Reset time
		void resetRun();

		// Return class variables
		int getHigh();
		int getLight();
		int getLow();
		int getMid();
		unsigned long getTime();

		// Update high, low, mid (and trigger)
		void updateAll();

	private:
		// Constructor parameters
		byte PIN;
		byte LED;

		// updateAll variables
		int _light;
		int _hi, _md, _lo;
		unsigned long _time;

};

#endif