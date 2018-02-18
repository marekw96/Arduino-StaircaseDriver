#ifndef PCF8574OutputPin_H
#define PCF8574OutputPin_H

#include <PCF8574.h>
#include <Wire.h>
#include "OutputPin.h"

class PCF8574OutputPin : public OutputPin
{
public:
	explicit PCF8574OutputPin(PCF8574& expander, int pin);
	void set(char value);
	~PCF8574OutputPin() = default;
private:
	PCF8574& expander;
	int pin_number;
};

#endif