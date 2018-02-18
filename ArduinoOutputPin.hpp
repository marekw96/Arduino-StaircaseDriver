#pragma once

#include "OutputPin.hpp"

class ArduinoOutputPin : public OutputPin
{
public:
	explicit ArduinoOutputPin(int pin);
	~ArduinoOutputPin() = default;
	void set(char value) override;

private:
	int pin_number;
};
