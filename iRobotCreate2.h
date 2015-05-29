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

enum Drive
{
	DriveStraight = 0x8000,
	DriveInPlaceClockwise = 0xFFFF,
	DriveInPlaceCounterClockwise = 0x0001,
};

enum ChargeState
{
	ChargeStateNotCharging = 0,
	ChargeStateReconditioningCharging = 1,
	ChargeStateFullChanrging = 2,
	ChargeStateTrickleCharging = 3,
	ChargeStateWaiting = 4,
	ChargeStateFault = 5,
};

enum packetIds {
	//all sent within packet 7, need to unpack byte upon retrival
	rightBumper = 101, 
	leftBumper = 102,
	rightWheelDrop = 103,
	leftWheelDrop = 104,
	//all sent within packet 14, need to unpack byte upon retrival
	sideBrushOvercurrent = 105,
	mainBrushOvercurrent = 106,
	rightWheelOvercurrent = 107,
	leftWheelOvercurrent = 108,
	//all sent within packet 18, need to unpack byte upon retrival
	cleanButton = 109,
	spotButton = 110,
	dockButton = 111,
	minuteButton = 112,
	hourButton = 113,
	dayButton = 114,
	scheduleButton = 115,
	clockButton = 116,
	//all sent within packet 45, need to unpack byte upon retrival
	lightBumperLeft = 117,
	lightBumperFrontLeft = 118,
	lightBumperCenterLeft = 119,
	lightBumperCenterRight = 120,
	lightBumperFrontRight = 121,
	lightBumperRight = 122,
	//boolean values
	wallSensor = 8,
	leftCliff = 9,
	frontLeftCliff = 10,
	frontRightCliff = 11,
	rightCliff = 12,
	virtualWall = 13,
	songPlaying = 37,
	stasis = 58,
	//byte values
	dirtDetector = 15,
	irOmnidirectional = 17,
	irLeft = 52,
	irRight = 53,
	chargingState = 21, //0-5
	chargingSources = 34, //0-3
	operationalMode = 35, //0-3
	songNumber = 36, //0-15
	streamPackets = 38, //0-108
	//char values
	batteryTempInC = 24,
	//int values
	distanceTraveled = 19,
	degreesTurned = 20,
	currentFlow = 23,
	wallSignal = 27, //0-1027
	leftCliffSignal = 28, //0-4095
	frontLeftCliffSignal = 29, //0-4095
	frontRightCliffSignal = 30, //0-4095
	rightCliffSignal = 31, //0-4095
	requestedVelocity = 39, //-500 - 500
	requestedRadius = 40, 
	requestedRightVelocity = 41, //-500 - 500
	requestedLeftVelocity = 42, //-500 - 500
	lightBumperLeftSignal = 46, //0-4095
	lightBumperFrontLeftSignal = 47, //0-4095
	lightBumperCenterLeftSignal = 48, //0-4095
	lightBumperCenterRightSignal = 49, //0-4095
	lightBumperFrontRightSignal = 50, //0-4095
	lightBumperRightSignal = 51, //0-4095
	leftMotorCurrent = 54,
	rightMotorCurrent = 55,
	mainBrushCurrent = 56,
	sideBrushCurrent = 57,
	//unsigned int values
	batteryVoltage = 22,
	batterCharge = 25,
	batteryCapacity = 26,
	leftEncoderCount = 43,
	rightEncoderCount = 44

};

enum notes{
	N_G1 = 31,
	N_G1S = 32,
	N_A1 = 33,
	N_A1S = 34,
	N_B1 = 35,
	N_C1 = 36,
	N_C1S = 37,
	N_D1 = 38,
	N_D1S = 39,
	N_E1 = 40,
	N_F1 = 41,
	N_F1S = 42,
	N_G2 = 43,
	N_G2S = 44,
	N_A2 = 45,
	N_A2S = 46,
	N_B2 = 47,
	N_C2 = 48,
	N_C2S = 49,
	N_D2 = 50,
	N_D2S = 51,
	N_E2 = 52,
	N_F2 = 53,
	N_F2S = 54,
	N_G3 = 55,
	N_G3S = 56,
	N_A3 = 57,
	N_A3S = 58,
	N_B3 = 59,
	N_C3 = 60,
	N_C3S = 61,
	N_D3 = 62,
	N_D3S = 63,
	N_E3 = 64,
	N_F3 = 65,
	N_F3S = 66,
	N_G4 = 67,
	N_G4S = 68,
	N_A4 = 69,
	N_A4S = 70,
	N_B4 = 71,
	N_C4 = 72,
	N_C4S = 73,
	N_D4 = 74,
	N_D4S = 75,
	N_E4 = 76,
	N_F4 = 77,
	N_F4S = 78,
	N_G5 = 79,
	N_G5S = 80,
	N_A5 = 81,
	N_A5S = 82,
	N_B5 = 83,
	N_C5 = 84,
	N_C5S = 85,
	N_D5 = 86,
	N_D5S = 87,
	N_E5 = 88,
	N_F5 = 89,
	N_F5S = 90,
	N_G6 = 91,
	N_G6S = 92,
	N_A6 = 93,
	N_A6S = 94,
	N_B6 = 95,
	N_C6 = 96,
	N_C6S = 97,
	N_D6 = 98,
	N_D6S = 99,
	N_E6 = 100,
	N_F6 = 101,
	N_F6S = 102,
	N_G7 = 103,
	N_G7S = 104,
	N_A7 = 105,
	N_A7S = 106,
	N_B7 = 107
};

//byte one_byte_data[22] = { 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 18, 21, 24, 34, 35, 36, 37, 38, 45, 52, 53, 58};

class iRobotCreate2 {
public:

	iRobotCreate2();
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


	//non blocking sensor functions
	void requestSensorData(byte sensorID);
	void requestSensorDataList(byte numOfRequests, byte requestIDs[]);
	void beginDataStream(byte numOfRequests, byte requestIDs[]);
	void pauseStream();
	void resumeSteam();

	//blocking sensor functions - these will request data and wait until a response is recieved, then return the response
	int getSensorData(byte sensorID);
	int * getSensorData(byte numOfRequests, byte requestIDs[]);

	void decodeIR(byte value);
	bool getSensorData(byte * buffer, byte bufferLength);


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
	bool _isPaused;
	bool _isStreaming;

	char _digit1;
	char _digit2;
	char _digit3;
	char _digit4;

	bool usingSoftSerial;
	SoftwareSerial softSerial;

};

#endif