#pragma once
#include "LedsController.hpp"
#include "MotionSensorController.hpp"
#include "Utility.hpp"
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
	void sleep_if_possible();
	void handle_sensors();
	void turn_leds_off_if_possible();

	LedsController leds;
	MotionSensorController motion_sensor;
	DEF::DIRECTION direction;
	elapsedMillis time_from_turned_leds;
	elapsedMillis time_from_last_activity;
};

