#include "ArduinoOutputPin.h"
#include <Arduino.h> 

ArduinoOutputPin::ArduinoOutputPin(int pin) : OutputPin{}, pin_number{pin}
{
	pinMode(pin_number, OUTPUT);
}

void ArduinoOutputPin::set(char value)
{
	::digitalWrite(pin_number, value);
}
