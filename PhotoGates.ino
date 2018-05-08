#include <PhotoGate.h>

// Constants Declarations and Initializations (Change at will.)
#define NUMGATES 2  // Number of photogates set up

// DON'T USE PIN 13!!!

#define CALIBBUTTON 8
#define STATSBUTTON 10
#define RESETBUTLED 12

// Create photoGate Array (FIX LATER)
PhotoGate photoGate[NUMGATES];

void setup() 
{
  for (unsigned i = 0 ; i < NUMGATES ; ++i)
  {
    photoGate[i].init(A0 + i, CALIBBUTTON);
  }
  
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial);	// Wait for serial port to connect. Needed for native USB port only.

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



void loop() 
{
	if (digitalRead(CALIBBUTTON) == LOW) 
	{
		Serial.println();
		Serial.println();
		Serial.println();
		Serial.println("Resetting all photogate calibrations...");
		// Reset all photogate calibrations
		for (int i = 0; i < NUMGATES; i++)
		{
			photoGate[i].resetCal();
		}
     
		Serial.println("All photogate calibrations are reset!");
	}



	if (digitalRead(RESETBUTTON) == LOW) 
	{    
		Serial.println();
		Serial.println();
		Serial.println();
		Serial.println("Resetting all photogate times...");
		// Reset all photogate times
		for (int i = 0; i < NUMGATES; i++)
    {
			photoGate[i].resetRun();
    }
     
		Serial.println("All photogate timers are reset!");
	}

	

	if (digitalRead(STATSBUTTON) == LOW) 
	{
		Serial.println();
		Serial.println();
		Serial.println();
		for (int i = 0; i < NUMGATES; i++) 
		{
			Serial.print("PhotoGate ");
			Serial.print(i + 1);
			Serial.print("'s TIME (in relative microseconds) is: ");
			Serial.print(photoGate[i].getTime());
			Serial.println();
		}
		Serial.print("The elapsed time (in microseconds) is: ");
		Serial.print(photoGate[1].getTime() - photoGate[0].getTime());
		Serial.println();
	}


  boolean resetLED = 0;
	for (int i = 0; i < NUMGATES; i++)
  {
		photoGate[i].updateAll();
    resetLED = resetLED || !photoGate[i].getTime();
  }
  if (resetLED)
  {
    digitalWrite(RESETBUTLED, HIGH);
  }
  else
  {
    digitalWrite(RESETBUTLED, LOW);
  }
}
