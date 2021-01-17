#include "StaricaseDriver.hpp"
#include "Arduino.h"
#include <avr/sleep.h>

StaircaseDriver::StaircaseDriver()
	: leds{}, motion_sensor{}, time_from_turned_leds{ 0 }, time_from_last_activity{ 0 }
{
}

void StaircaseDriver::init()
{
	set_sleep_mode(DEF::SLEEP_MODE);
	sleep_enable();

	leds.init();
	motion_sensor.init();
}

void StaircaseDriver::step()
{
	//sleep_if_possible();

	turn_leds_off_if_possible();
	handle_sensors();

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

void StaircaseDriver::sleep_if_possible()
{
	if (leds.get_status() == DEF::LEDS_STATUS::OFF)
	{
		if (time_from_last_activity > DEF::SLEEP_AFTER)
		{
			sleep_mode();
			sleep_disable();
		}
	}
	else
	{
		time_from_last_activity = 0;
	}
}

void StaircaseDriver::handle_sensors()
{
	auto interrupts = motion_sensor.get_interrupts();
	if (interrupts & DEF::SENSOR_INTERRUPT::TOP)
	{
		direction = DEF::DIRECTION::TOP;
		leds.step_on_to(direction);
		time_from_turned_leds = 0;
	}

	if (interrupts & DEF::SENSOR_INTERRUPT::BOTTOM)
	{
		direction = DEF::DIRECTION::BOTTOM;
		leds.step_on_to(direction);
		time_from_turned_leds = 0;
	}
}

void StaircaseDriver::turn_leds_off_if_possible()
{
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
}
