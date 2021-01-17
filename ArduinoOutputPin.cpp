#include "ArduinoOutputPin.hpp"
#include <Arduino.h> 
#include "Utility.hpp"

ArduinoOutputPin::ArduinoOutputPin(int pin) : OutputPin{}, pin_number{pin}
{
	pinMode(pin_number, OUTPUT);
}

void ArduinoOutputPin::set(char value)
{
	::digitalWrite(pin_number, value);
  Serial.print("PIN ");
  Serial.print(pin_number);
  Serial.print(" value ");
  Serial.println(value==DEF::ON?"ON":"OFF");
}
