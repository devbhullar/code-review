#pragma once

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class Linear_Actuator
{
public:
	Linear_Actuator(uint8_t ID, uint8_t pin);
	Adafruit_DCMotor *motor = nullptr;
	void begin(bool afms);
	uint16_t getPotValue();
	uint16_t getPos_mm();
	void setPos(uint16_t pos_mm);
	uint16_t stroke_mm = 200;
	uint8_t margin = 5;
	bool released = false;
	bool debug = false;

private:
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	uint8_t potPin;
	uint16_t currentPos;
	uint8_t id;
};

Linear_Actuator::Linear_Actuator(uint8_t ID, uint8_t pin)
{
	motor = AFMS.getMotor(ID);
	potPin = pin;
	id = ID;
}

void Linear_Actuator::begin(bool afms)
{
	if (afms)
	{
		AFMS.begin();
	}
	motor->setSpeed(255);
}

uint16_t Linear_Actuator::getPotValue()
{
	return analogRead(potPin);
}

uint16_t Linear_Actuator::getPos_mm()
{
	return map(analogRead(potPin), 0, 1023, 0, stroke_mm);
}

void Linear_Actuator::setPos(uint16_t targetPos_mm)
{
	uint16_t targetPos = map(targetPos_mm, 0, stroke_mm, 0, 1023);
	currentPos = Linear_Actuator::getPotValue();
	uint16_t currentPos_mm = getPos_mm();
	released = false;

	if ((currentPos_mm < targetPos_mm) && (abs(currentPos_mm - targetPos_mm) > margin))
	{
		motor->run(FORWARD);

		if (debug)
		{
			Serial.print("Linear actuator ID ");
			Serial.print(id);
			Serial.print(" moving FORWARD. Current Pos = ");
			Serial.print(currentPos_mm);
			Serial.print(" , Target Pos = ");
			Serial.println(targetPos_mm);
		}
	}
	if ((currentPos_mm > targetPos_mm) && (abs(currentPos_mm - targetPos_mm) > margin))
	{
		motor->run(BACKWARD);
		
		if (debug)
		{
			Serial.print("Linear actuator ID ");
			Serial.print(id);
			Serial.print(" moving BACKWARD. Current Pos = ");
			Serial.print(currentPos_mm);
			Serial.print(" , Target Pos = ");
			Serial.println(targetPos_mm);
		}
	}
	if (abs(currentPos_mm - targetPos_mm) < margin)
	{
		motor->run(RELEASE);
		released = true;
		
		if (debug)
		{
			Serial.print("Linear actuator ID ");
			Serial.print(id);
			Serial.print(" STOPPED. Current Pos = ");
			Serial.print(currentPos_mm);
			Serial.print(" , Target Pos = ");
			Serial.println(targetPos_mm);
		}
	}
}



