#pragma once

#include "Arduino.h"

namespace DEF
{
	const int ON = LOW;
	const int OFF = HIGH;

	namespace ExpanderAddress
	{
		const uint8_t FIRST = 33;
		const uint8_t SECOND = 34;
	}

	enum class LEDS_STATUS { ON, 
							TURNING_ON_TO_TOP,
							TURNING_ON_TO_BOTTOM, 
							TURNING_OFF_FROM_TOP, 
							TURNING_OFF_FROM_BOTTOM, 
							OFF};

	const int TURNING_ON_TIME = 1000;
	const int TIME_TO_TURNING_OFF = 0;
	const int TURNING_OFF_TIME = 1000;

	enum class DIRECTION { BOTTOM, TOP};

	const int BOTTOM_SENSOR_PIN = 2;
	const int TOP_SENSOR_PIN = 3;

	namespace SENSOR_INTERRUPT
	{
		const int BOTTOM = 1;
		const int TOP = 2;
	}

	const int LEDS_NUM = 18;

	const int SENSOR_SIGNAL_ON = LOW;

	const int SENSOR_INTERRUPT_TYPE = FALLING;
}