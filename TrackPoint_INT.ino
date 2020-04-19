 #include <Mouse.h>

/*
 * Created on 14/03/2014
 * Author: Cong Nguyen
 *
 * Using an Arduino Leonardo to interface with a TrackPoint
 * Pin 3 (int.0)	: CLOCK  SCL TP_6
 * Pin 2			: DATA  SDA TP_1
 * Pin 4			: RESET  TP_2
 * 
 * Using Teensy 2.0 
 * PIN_D0 (5): CLOCK  SCL TP_6
 * PIN_D1 (6): DATA  SDA TP_1
 * PIN_D2 (7): RESET  TP_2
 */
#include "TrackPoint.h"

#define CLOCK		3
#define DATA		2
#define RESET		0
#define CLOCK_INT	0

TrackPoint trackpoint(CLOCK, DATA, RESET, true);

void setup()
{	
	Mouse.begin();

	trackpoint.reset();
	trackpoint.setSensitivityFactor(0xC0);
	trackpoint.setStreamMode();

	attachInterrupt(CLOCK_INT, clockInterrupt, FALLING);
}

void loop()
{	
	if(trackpoint.reportAvailable()) {
		TrackPoint::DataReport d = trackpoint.getStreamReport();
		Mouse.move(d.x, -d.y, 0);
		Serial.println(d.state % 16 % 7);  // mouse button value
	} 
	
}

void clockInterrupt(void) {
	trackpoint.getDataBit();
}
