#pragma once
class MotionSensorController
{
public:
	static bool bottom_sensor_interrupt;
	static bool top_sensor_interrupt;

	MotionSensorController();

	void init();
	void step();
	int get_interrupts();

private:
};

