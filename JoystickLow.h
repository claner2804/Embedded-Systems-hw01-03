
#ifndef JOYSTICKLOW_H_
#define JOYSTICKLOW_H_

#include <stdint.h>

class JoystickLow {
public:
	JoystickLow(int pinX, int pinY, int pinButton);

	void begin();
	void update();
	int16_t getPosX(bool immediate = false);
	int16_t getPosY(bool immediate = false);
	bool getButton(bool immediate = false);
	void setDeadzone(int16_t deadzone);
	int16_t getDeadzone();

private:
	int pinX;
	int pinY;
	int16_t posX = 0;
	int16_t posY = 0;
	uint8_t button = 0;
	int16_t deadzone = 30;
	int16_t rawReadValue(int pin);
};

#endif /* JOYSTICKLOW_H_ */
