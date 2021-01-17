#pragma once
#include "OutputPin.hpp"
#include "Utility.hpp"
#include <elapsedMillis.h>

class LedsController
{
public:
	LedsController();
	~LedsController();
	void init();
	void turn_off();
	void turn_on();
	void step();
	DEF::LEDS_STATUS get_status();
	void step_on_to(DEF::DIRECTION direction);
	void step_off_to(DEF::DIRECTION direction);

private:
	void led_step_on_to_top();
	void led_step_on_to_bottom();
	void led_step_off_from_top();
	void led_step_off_from_bottom();
  void led_step_on_to_top_additional();
  void led_step_on_to_bottom_additional();

	OutputPin* pins[DEF::LEDS_NUM];
	int max_led_index;

	DEF::LEDS_STATUS leds_status;
	int actual_step;
  int additional_step;
  DEF::LEDS_STATUS additional_status;
	elapsedMillis step_last_activity;
  elapsedMillis additional_step_last_acitivity;
};
