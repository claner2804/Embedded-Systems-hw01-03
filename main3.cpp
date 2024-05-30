#include <Arduino.h>
#include "JoystickLow.h"

JoystickLow js(A0, A1, 0);

void setup() {
	Serial.begin(115200);
	js.begin();
	Serial.println("Everything has been initialized");
}


void loop() {
	js.update();
	Serial.print("X = ");
	Serial.print(js.getPosX());
	Serial.print(", Y = ");
	Serial.print(js.getPosY());
	Serial.print(", Button = ");
	Serial.println(js.getButton());
	delay(500);
}