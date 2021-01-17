#include "StaricaseDriver.hpp"

StaircaseDriver driver;
void setup() {
    Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//
//  }
  Serial.println("setup");
	driver.init();
}

void loop() {
	driver.step();
//  Serial.println("loop");
}
