#ifndef IROBOTCREATE2_H
#define IROBOTCREATE2_H

// Arduino versioning.
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SoftwareSerial.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#define clamp(value, min, max) (value < min ? min : value > max ? max : value)

enum ScheduleDayOfWeek {
	Sunday = 1,
	Monday = 2,
	Tuesday = 4,
	Wednesday = 8,
	Thursday = 16,
	Friday = 32,
	Saturday = 64
};

enum SetDayOfWeek {
	Sun = 0,
	Mon = 1,
	Tues = 2,
	Weds = 3,
	Thurs = 4,
	Fri = 5,
	Sat = 6
};

enum iRobotButtons {
	Clean = 1,
	Spot = 2,
	Dock = 4,
	Minute = 8,
	Hour = 16,
	Day = 32,
	Schedule = 64,
	Clock = 128
};

struct Notes {
	byte note;
	byte duration;
};


class iRobotCreate2 {
public:

	iRobotCreate2(bool useSoftSerial, byte rxPin, byte txPin, byte baudRateChangePin);

	//available as passive safe or full modes
	void start();
	void reset();
	void stop();
	void resetBaudRate();
	void baud(long rate);
	void safeMode();
	void fullMode();
	void passiveMode();
	void clean();
	void maxClean();
	void spotClean();
	void seekDock();
	void turnOff();
	void schedule(byte days, byte hour[], byte minute[]);
	void setTime(SetDayOfWeek day, byte hour, byte minute);
	void pushButton(byte button);

	void createSong(byte songNumber, byte numberOfNotes, Notes notes[]);
	void playSong(byte songNumber);


	//available is safe or full modes
	//wheel motors
	void drive(int velocity, int radius);
	void driveWheels(int right, int left);
	void driveLeft(int left);
	void driveRight(int right);
	void driveWheelsPWM(int rightPWM, int leftPWM);
	//cleaning motors
	void enableBrushes(bool mainBrushDirection, bool sideBrushDirection, bool mainBrush, bool vacuum, bool sideBrush);
	void setMainBrush(bool direction, bool enable);
	void setSideBrush(bool direction, bool enable);
	void enableVacuum(bool enable);
	void setMainBrushSpeed(char speed);
	void setSideBrushSpeed(char speed);
	void setVaccumSpeed(char speed);
	//leds
	void setPowerLEDs(byte color, byte intensity);
	void setDebrisLED(bool enable);
	void setSpotLED(bool enable);
	void setDockLED(bool enable);
	void setWarningLED(bool enable);
	void setScheduleLEDs(byte days, bool schedule, bool clock, bool am, bool pm, bool colon);
	void setDigitLEDs(byte digit1, byte digit2, byte digit3, byte digit4);
	void setDigitLEDFromASCII(byte digit, char letter);


	//sensor functions
	void requestSensorData(byte sensorID);



protected:
	byte _color;
	byte _intensity;
	byte _brcPin;
	bool _mainBrushDirection;
	bool _sideBrushDirection;
	bool _mainBrush;
	bool _sideBrush;
	bool _vacuum;
	int _mainBrushSpeed;
	int _sideBrushSpeed;
	int _vacuumSpeed;
	bool _debrisLED;
	bool _spotLED;
	bool _dockLED;
	bool _warningLED;

	char _digit1;
	char _digit2;
	char _digit3;
	char _digit4;

	bool usingSoftSerial;
	SoftwareSerial softSerial;

};

#endif