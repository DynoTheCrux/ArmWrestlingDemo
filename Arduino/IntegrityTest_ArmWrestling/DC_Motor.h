// DC_Motor.h

#ifndef _DC_MOTOR_h
#define _DC_MOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DC_Motor{

public:
	DC_Motor(uint8_t dirPin, uint8_t pwmPin);

	void turn(bool dir, uint8_t pwm);
	void turn(uint8_t pwm);

	void setDir(bool dir);

	void turnCW(uint8_t pwm);
	void turnCCW(uint8_t pwm);

private:
	uint8_t _dirPin;
	uint8_t _pwmPin;

	bool _dir;	//0 is CW, 1 is CCW
};

#endif
