#include "LedsController.hpp"
#include "ArduinoOutputPin.hpp"


LedsController::LedsController()
	: max_led_index{ DEF::LEDS_NUM - 1 },
	leds_status{ DEF::LEDS_STATUS::OFF }, actual_step{ 0 }, step_last_activity { 0 }
{
}

LedsController::~LedsController()
{
//	for (auto pin : pins)
//		delete pin;
}

void LedsController::init()
{

//	int i = 0;
//	pins[i++] = new ArduinoOutputPin(22);
//	pins[i++] = new ArduinoOutputPin(23);
  
  for(int i = 0; i < DEF::LEDS_NUM; ++i)
    pins[i] = new ArduinoOutputPin(DEF::START_LED + i);
    

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
