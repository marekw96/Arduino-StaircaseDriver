#pragma once
#include "LedsController.h"
#include "MotionSensorController.h"
#include "Utility.h"
#include <elapsedMillis.h>

class StaircaseDriver
{
public:
	StaircaseDriver();
	void init();
	void step();

private:	
	void turn_off_leds();
	bool could_turn_off();

	LedsController leds;
	MotionSensorController motion_sensor;
	DEF::DIRECTION direction;
	elapsedMillis time_from_turned_leds;
};

