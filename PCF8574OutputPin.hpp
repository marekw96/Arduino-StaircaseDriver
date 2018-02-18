#pragma once

#include <PCF8574.h>
#include <Wire.h>
#include "OutputPin.hpp"

class PCF8574OutputPin : public OutputPin
{
public:
	explicit PCF8574OutputPin(PCF8574& expander, int pin);
	void set(char value) override;
	~PCF8574OutputPin() = default;
private:
	PCF8574& expander;
	int pin_number;
};