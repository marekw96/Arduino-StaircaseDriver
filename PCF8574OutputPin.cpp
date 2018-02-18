#include "PCF8574OutputPin.h"
#include <Arduino.h> 

PCF8574OutputPin::PCF8574OutputPin(PCF8574& expander, int pin) : OutputPin{}, expander{expander}, pin_number{pin}
{
	expander.pinMode(pin_number, OUTPUT);
}

void PCF8574OutputPin::set(char value)
{
	expander.digitalWrite(pin_number, value);
}
