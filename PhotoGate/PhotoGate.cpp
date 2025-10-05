/*
	PhotoGate.cpp - Library for PhotoGate control.
	Created by Rahul Goyal, August 19, 2017.
	Released to Cal Poly Baja SAE. ;)
*/

#include <Arduino.h>
#include "PhotoGate.h"

PhotoGate::PhotoGate() {}

void PhotoGate::begin(int pin) {
	// Pins
	PIN = pin;
	LED = pin - A0 + 8;		// Status LED
	pinMode(PIN, INPUT);
	pinMode(LED, OUTPUT);

	resetCal();
	resetRun();
}

void PhotoGate::resetCal() {
	// Reset high and low
	_hi = 0;
	_lo = 1023;
}

void PhotoGate::resetRun() {
	// Reset time
	_time = 0;
}

int PhotoGate::getHigh() {
	return _hi;
}

int PhotoGate::getLight() {
	return _light;
}

int PhotoGate::getLow() {
	return _lo;
}

int PhotoGate::getMid() {
	return _md;
}

unsigned long PhotoGate::getTime() {
	return _time;
}

void PhotoGate::updateAll() {
	// Read light
	_light = analogRead(PIN);

	// Update high
	if (_light > _hi) {
		_hi = _light;
		Serial.println("Calibrating high...");
	}

	// Update low
	if (_light < _lo) {
		_lo = _light;
		Serial.println("Calibrating low...");
	}

	// Update mid (tune this)
	_md = (_lo + _hi) / 2;

	// Check if blocked
	if (_light < _md) {
		if (!_time) {
			_time = micros();
			Serial.println("Time recorded!");
		}
		// Serial.println("Blocked!");
		digitalWrite(LED, HIGH);	// Turn status LED on
	} else {
		digitalWrite(LED, LOW);		// Turn status LED off
	}
}