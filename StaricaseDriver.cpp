#include "StaricaseDriver.hpp"
#include "Arduino.h"

StaircaseDriver::StaircaseDriver()
	: leds{}, motion_sensor{}, time_from_turned_leds{ 0 }
{
}

void StaircaseDriver::init()
{
	Serial.begin(9600);

	leds.init();
	motion_sensor.init();
}

void StaircaseDriver::step()
{
	auto interrupts = motion_sensor.get_interrupts();

	if (leds.get_status() == DEF::LEDS_STATUS::ON)
	{
		if (could_turn_off())
		{
			turn_off_leds();
		}
	}
	else
	{
		time_from_turned_leds = 0;
	}

	if (interrupts & DEF::SENSOR_INTERRUPT::TOP)
	{
		direction = DEF::DIRECTION::TOP;
	}

	if (interrupts & DEF::SENSOR_INTERRUPT::BOTTOM)
	{
		direction = DEF::DIRECTION::BOTTOM;
	}

	if (interrupts)
	{
		leds.step_on_to(direction);
		time_from_turned_leds = 0;
	}

	leds.step();
	motion_sensor.step();
}

void StaircaseDriver::turn_off_leds()
{
	leds.step_off_to(direction);
}

bool StaircaseDriver::could_turn_off()
{
	return time_from_turned_leds > DEF::TIME_TO_TURNING_OFF;
}

