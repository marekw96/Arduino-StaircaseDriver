#ifndef ArduinoOutputPin_H
#define ArduinoOutputPin_H

#include "OutputPin.h"

class ArduinoOutputPin : public OutputPin
{
public:
	explicit ArduinoOutputPin(int pin);
	~ArduinoOutputPin() = default;
	void set(char value);

private:
	int pin_number;
};

#endif