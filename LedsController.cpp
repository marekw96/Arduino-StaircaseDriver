#include "LedsController.h"
#include "PCF8574OutputPin.h"
#include "ArduinoOutputPin.h"


LedsController::LedsController()
	: max_led_index{ DEF::LEDS_NUM - 1 },
	leds_status{ DEF::LEDS_STATUS::OFF }, actual_step{ 0 }, step_last_activity { 0 }
{
}

LedsController::~LedsController()
{
	for (auto pin : pins)
		delete pin;
}

void LedsController::init()
{
	expander_1.begin(DEF::ExpanderAddress::FIRST);
	expander_2.begin(DEF::ExpanderAddress::SECOND);

	int i = 0;
	pins[i++] = new PCF8574OutputPin(expander_1, 0);
	pins[i++] = new PCF8574OutputPin(expander_1, 1);
	pins[i++] = new PCF8574OutputPin(expander_1, 2);
	pins[i++] = new PCF8574OutputPin(expander_1, 3);
	pins[i++] = new PCF8574OutputPin(expander_1, 4);
	pins[i++] = new PCF8574OutputPin(expander_1, 5);
	pins[i++] = new PCF8574OutputPin(expander_1, 6);
	pins[i++] = new PCF8574OutputPin(expander_1, 7);
	pins[i++] = new PCF8574OutputPin(expander_2, 0);
	pins[i++] = new PCF8574OutputPin(expander_2, 1);
	pins[i++] = new PCF8574OutputPin(expander_2, 2);
	pins[i++] = new PCF8574OutputPin(expander_2, 3);
	pins[i++] = new PCF8574OutputPin(expander_2, 4);
	pins[i++] = new PCF8574OutputPin(expander_2, 5);
	pins[i++] = new PCF8574OutputPin(expander_2, 6);
	pins[i++] = new PCF8574OutputPin(expander_2, 7);
	pins[i++] = new ArduinoOutputPin(11);
	pins[i++] = new ArduinoOutputPin(12);

	turn_off();
}

void LedsController::turn_off()
{
	for (auto pin : pins)
		pin->set(DEF::OFF);
}

void LedsController::turn_on()
{
	for (auto pin : pins)
		pin->set(DEF::ON);
}

void LedsController::step()
{
	switch (leds_status)
	{
	case DEF::LEDS_STATUS::TURNING_ON_TO_TOP:
		led_step_on_to_top();
		break;
	case DEF::LEDS_STATUS::TURNING_ON_TO_BOTTOM:
		led_step_on_to_bottom();
		break;
	case DEF::LEDS_STATUS::TURNING_OFF_FROM_TOP:
		led_step_off_from_top();
		break;
	case DEF::LEDS_STATUS::TURNING_OFF_FROM_BOTTOM:
		led_step_off_from_bottom();
		break;
	default:
		return;
	}
}

DEF::LEDS_STATUS LedsController::get_status()
{
	return leds_status;
}

void LedsController::step_on_to(DEF::DIRECTION direction)
{
	auto status = get_status();

	if (status == DEF::LEDS_STATUS::ON)
		return;

	else if (status == DEF::LEDS_STATUS::OFF)
	{
		switch (direction)
		{
			case DEF::DIRECTION::TOP:
				actual_step = 0;
				leds_status = DEF::LEDS_STATUS::TURNING_ON_TO_TOP;
				break;
			case DEF::DIRECTION::BOTTOM:
				actual_step = max_led_index;
				leds_status = DEF::LEDS_STATUS::TURNING_ON_TO_BOTTOM;
				break;
		}

		return;
	}

	else if (status == DEF::LEDS_STATUS::TURNING_OFF_FROM_TOP)
	{
		leds_status = DEF::LEDS_STATUS::TURNING_ON_TO_TOP;
	}

	else if (status == DEF::LEDS_STATUS::TURNING_OFF_FROM_BOTTOM)
	{
		leds_status = DEF::LEDS_STATUS::TURNING_ON_TO_BOTTOM;
	}
}

void LedsController::step_off_to(DEF::DIRECTION direction)
{
	auto status = get_status();

	if (status == DEF::LEDS_STATUS::OFF)
		return;

	else if (status == DEF::LEDS_STATUS::ON)
	{
		switch (direction)
		{
		case DEF::DIRECTION::TOP:
			actual_step = 0;
			leds_status = DEF::LEDS_STATUS::TURNING_OFF_FROM_BOTTOM;
			break;
		case DEF::DIRECTION::BOTTOM:
			actual_step = max_led_index;
			leds_status = DEF::LEDS_STATUS::TURNING_OFF_FROM_TOP;
			break;
		}

		return;
	}
}

void LedsController::led_step_on_to_top()
{
	if (step_last_activity < DEF::TURNING_ON_TIME)
		return;

	step_last_activity = 0;
	pins[actual_step++]->set(DEF::ON);

	if (actual_step > max_led_index)
	{
		leds_status = DEF::LEDS_STATUS::ON;
		actual_step = max_led_index;
	}
}

void LedsController::led_step_on_to_bottom()
{
	if (step_last_activity < DEF::TURNING_ON_TIME)
		return;

	step_last_activity = 0;
	pins[actual_step--]->set(DEF::ON);

	if (actual_step < 0)
	{
		leds_status = DEF::LEDS_STATUS::ON;
		actual_step = 0;
	}
}

void LedsController::led_step_off_from_top()
{
	if (step_last_activity < DEF::TURNING_OFF_TIME)
		return;

	step_last_activity = 0;
	pins[actual_step--]->set(DEF::OFF);

	if (actual_step < 0)
	{
		leds_status = DEF::LEDS_STATUS::OFF;
		actual_step = 0;
	}
}

void LedsController::led_step_off_from_bottom()
{
	if (step_last_activity < DEF::TURNING_OFF_TIME)
		return;

	step_last_activity = 0;
	pins[actual_step++]->set(DEF::OFF);

	if (actual_step > max_led_index)
	{
		leds_status = DEF::LEDS_STATUS::OFF;
		actual_step = max_led_index;
	}
}

