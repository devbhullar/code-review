#include "Linear_Actuator.h"

Linear_Actuator testActuator1 = Linear_Actuator(1, A0);
Linear_Actuator testActuator2 = Linear_Actuator(2, A1);
Linear_Actuator testActuator3 = Linear_Actuator(3, A2);
Linear_Actuator testActuator4 = Linear_Actuator(4, A3);
String inData;
uint16_t d1 = 0;
uint16_t d2 = 0;
uint16_t d3 = 0;
uint16_t d4 = 0;

void setup()
{
	Serial.begin(9600);
	testActuator1.begin(1);
	testActuator2.begin(0);
	testActuator3.begin(0);
	testActuator4.begin(0);
	
	testActuator4.stroke_mm = 50;
}

void loop()
{
	
	while (Serial.available() > 0)
	{
		char recieved = Serial.read();
		inData += recieved;

		// Process message when new line character is recieved
		if (recieved == '\n')
		{
			// format of inData = "axbycz\n" where x, y and z are
			// numbers for lengths of actuators 1, 2, and 3 respectively
			d1 = (inData.substring(1, inData.indexOf('b'))).toInt();
			d2 = (inData.substring(inData.indexOf('b') + 1, inData.indexOf('c'))).toInt();
			d3 = (inData.substring(inData.indexOf('c') + 1, inData.indexOf('d'))).toInt();
			d4 = (inData.substring(inData.indexOf('d') + 1, inData.indexOf('\n'))).toInt();
			/*Serial.println(d1);
			Serial.println(d2);
			Serial.println(d3);
			Serial.println(d4);*/

			inData = ""; // Clear recieved buffer
		}
	}

	testActuator1.setPos(d1);
	testActuator2.setPos(d2);
	testActuator3.setPos(d3);
	testActuator4.setPos(d4);
}
