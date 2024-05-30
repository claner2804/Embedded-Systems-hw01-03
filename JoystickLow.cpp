#include "JoystickLow.h"

#include <avr/io.h>

#define ABS(x)		((x)>=0 ? (x) : -(x))

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

JoystickLow::JoystickLow(int pinX, int pinY, int pinButton)
	: pinX(pinX), pinY(pinY) {
}

void JoystickLow::begin() {
	DDRE = DDRE & ~(1 << PE2); // PE2 als Digitaleingang konfigurieren
	PORTE = PORTE & ~(1 << PE2); // Pullup-Widerstand für PE2 ausschalten
}

void JoystickLow::update() {
	posX = getPosX(true);
	posY = getPosY(true);
	button = getButton(true);
}



int16_t JoystickLow::getPosX(bool immediate) {
	if (immediate) {
		int16_t value = rawReadValue(7);
		if (ABS(value) <= deadzone) {
			value = 0;
		}
		return value;
	} else {
		return posX;
	}
}

int16_t JoystickLow::getPosY(bool immediate) {
	if (immediate) {
		int16_t value = rawReadValue(6);
		if (ABS(value) <= deadzone) {
			value = 0;
		}
		return value;
	} else {
		return posY;
	}
}

bool JoystickLow::getButton(bool immediate) {
	if (immediate) {
		return PINE & (1 << PE2);
	} else {
		return button;
	}
}

void JoystickLow::setDeadzone(int16_t deadzone) {
	this->deadzone = ABS(deadzone);
}

int16_t JoystickLow::getDeadzone() {
	return deadzone;
}

int16_t JoystickLow::rawReadValue(int pin) {
	// Konfiguriere die Betriebsspannung als Referenzspannung, und wähle Analogeingang ADC5 aus
	ADMUX = (1 << REFS0) | pin;

	// Schalte den Analog/Digital-Wandler ein, und setzt einen passenden Prescaler-Wert
	// Analog/Digital-Wandler-Frequenz = CPU-Frequenz / Prescaler-Wert
	// Die Wandler-Frequenz sollte zwischen 50kHz und 200kHz liegen
	// In unserem Fall: 16MHz / 128 = 125kHz
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

	// Starte den Umwandlungsprozess zum Auslesen des Helligkeitssensors
	ADCSRA = ADCSRA | (1 << ADSC);

	// Solange das ADSC-Bit im ADCSRA Register 1 ist, ist der Umwandlungsprozess noch nicht abgeschlossen
	// Daher warten wir, bis dieses Bit 0 ist
	while (ADCSRA & (1 << ADSC));

	// Lese das Umwandlungsergebnis aus
	int low = ADCL; // Zuerst immer ADCL auslesen!
	int high = ADCH; // Erst dann ADCH auslesen!
	int value = (high << 8) | low; // Das endgültige Ergebnis zusammenbauen

	value = map(value, 0, 1023, -512, 512);
	return value;
}