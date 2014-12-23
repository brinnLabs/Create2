// iRobotCreate2.cpp
//
// Copyright (C) 2014 Dom Amato
// MIT Licence

#include "iRobotCreate2.h"

iRobotCreate2::iRobotCreate2(bool useSoftSerial, byte rxPin, byte txPin, byte baudRateChangePin){
	usingSoftSerial = useSoftSerial;
	_brcPin = baudRateChangePin;

	if (useSoftSerial){
		//SoftwareSerial newSS(rxPin, txPin);
		softSerial = SoftwareSerial(rxPin, txPin);
		softSerial.begin(19200);
	}
	else {
		Serial.begin(19200);
	}
	_mainBrushDirection = false;
	_sideBrushDirection = false;
	_mainBrush = false;
	_sideBrush = false;
	_vacuum = false;
	_mainBrushSpeed = 0;
	_sideBrushSpeed = 0;
	_vacuumSpeed = 0;
	_debrisLED = false;
	_spotLED = false;
	_dockLED = false;
	_warningLED = false;

	_isPaused = false;
	_isStreaming = false;

	_digit1 = 0;
	_digit2 = 0;
	_digit3 = 0;
	_digit4 = 0;
}

//available as passive safe or full modes
void iRobotCreate2::start(){
	if (usingSoftSerial){
		softSerial.write(128);
	}
	else {
		Serial.write(128);
	}
}
void iRobotCreate2::reset(){
	if (usingSoftSerial){
		softSerial.write(7);
	}
	else {
		Serial.write(7);
	}
}

void iRobotCreate2::resetBaudRate(){
	pinMode(_brcPin, OUTPUT);
	delay(2000);
	digitalWrite(13, HIGH);
	digitalWrite(_brcPin, HIGH);
	for (int i = 0; i < 3; i++){
		digitalWrite(13, LOW);
		digitalWrite(_brcPin, LOW);
		delay(200);
		digitalWrite(13, HIGH);
		digitalWrite(_brcPin, HIGH);
		delay(200);
	}
	start();
}

void iRobotCreate2::stop(){
	if (usingSoftSerial){
		softSerial.write(173);
	}
	else {
		Serial.write(173);
	}
}
void iRobotCreate2::baud(long rate){
	byte baudCode = 7;
	switch (rate){
	case 300:
		baudCode = 0;
		break;
	case 600:
		baudCode = 1;
		break;
	case 1200:
		baudCode = 2;
		break;
	case 2400:
		baudCode = 3;
		break;
	case 4800:
		baudCode = 4;
		break;
	case 9600:
		baudCode = 5;
		break;
	case 14400:
		baudCode = 6;
		break;
	case 19200:
		baudCode = 7;
		break;
	case 28800:
		baudCode = 8;
		break;
	case 38400:
		baudCode = 9;
		break;
	case 57600:
		baudCode = 10;
		break;
	case 115200:
		baudCode = 11;
		break;
	}
	if (usingSoftSerial){
		softSerial.write(129);
		softSerial.write(baudCode);
	}
	else {
		Serial.write(129);
		Serial.write(baudCode);
		Serial.begin(rate);
	}
}
void iRobotCreate2::safeMode(){
	if (usingSoftSerial){
		softSerial.write(131);
	}
	else {
		Serial.write(131);
	}
}
void iRobotCreate2::fullMode(){
	if (usingSoftSerial){
		softSerial.write(132);
	}
	else {
		Serial.write(132);
	}
}
void iRobotCreate2::passiveMode(){
	start();
}
void iRobotCreate2::clean(){
	if (usingSoftSerial){
		softSerial.write(135);
	}
	else {
		Serial.write(135);
	}
}
void iRobotCreate2::maxClean(){
	if (usingSoftSerial){
		softSerial.write(136);
	}
	else {
		Serial.write(136);
	}
}
void iRobotCreate2::spotClean(){
	if (usingSoftSerial){
		softSerial.write(134);
	}
	else {
		Serial.write(134);
	}
}
void iRobotCreate2::seekDock(){
	if (usingSoftSerial){
		softSerial.write(143);
	}
	else {
		Serial.write(143);
	}
}
void iRobotCreate2::turnOff(){
	if (usingSoftSerial){
		softSerial.write(133);
	}
	else {
		Serial.write(133);
	}
}
void iRobotCreate2::schedule(byte days, byte hour[], byte minute[]){
	if (usingSoftSerial){
		softSerial.write(167);
		softSerial.write(days);
		int timeCounter = 0;
		for (int i = 0; i < 8; i++){
			if (CHECK_BIT(days, i)){
				softSerial.write(hour[timeCounter]);
				softSerial.write(minute[timeCounter++]);
			}
			else {
				softSerial.write((byte)0x00);
				softSerial.write((byte)0x00);
			}
		}
	}
	else {
		Serial.write(167);
		Serial.write(days);
		int timeCounter = 0;
		for (int i = 0; i < 8; i++){
			if (CHECK_BIT(days, i)){
				Serial.write(hour[timeCounter]);
				Serial.write(minute[timeCounter++]);
			}
			else {
				Serial.write((byte)0x00);
				Serial.write((byte)0x00);
			}
		}
	}
}
void iRobotCreate2::setTime(SetDayOfWeek day, byte hour, byte minute){
	if (usingSoftSerial){
		softSerial.write(168);
		softSerial.write(day);
		softSerial.write(hour);
		softSerial.write(minute);

	}
	else {
		Serial.write(168);
		Serial.write(day);

		Serial.write(hour);
		Serial.write(minute);

	}
}
void iRobotCreate2::pushButton(byte button){
	if (usingSoftSerial){
		softSerial.write(165);
		softSerial.write(button);
	}
	else {
		Serial.write(165);
		Serial.write(button);
	}
}
//play songs
void iRobotCreate2::createSong(byte songNumber, byte numberOfNotes, Notes notes[]){
	if (usingSoftSerial){
		softSerial.write(140);
		softSerial.write(songNumber);
		softSerial.write(numberOfNotes);
		for (int i = 0; i < numberOfNotes; i++){
			softSerial.write(notes[i].note);
			softSerial.write(notes[i].duration);
		}
	}
	else {
		Serial.write(140);
		Serial.write(songNumber);
		Serial.write(numberOfNotes);
		for (int i = 0; i < numberOfNotes; i++){
			Serial.write(notes[i].note);
			Serial.write(notes[i].duration);
		}
	}
}

void iRobotCreate2::playSong(byte songNumber){
	if (usingSoftSerial){
		softSerial.write(141);
		softSerial.write(songNumber);
	}
	else {
		Serial.write(141);
		Serial.write(songNumber);
	}
}


//available is safe or full modes
//wheel motors
void iRobotCreate2::drive(int velocity, int radius){
	clamp(velocity, -500, 500);
	clamp(radius, -2000, 2000);
	if (usingSoftSerial){
		softSerial.write(137);
		softSerial.write(velocity & 0x7F);
		softSerial.write((velocity >> 7) & 0x7F);
		softSerial.write(radius & 0x7F);
		softSerial.write((radius >> 7) & 0x7F);
	}
	else {
		softSerial.write(137);
		softSerial.write(velocity & 0x7F);
		softSerial.write((velocity >> 7) & 0x7F);
		softSerial.write(radius & 0x7F);
		softSerial.write((radius >> 7) & 0x7F);
	}
}
void iRobotCreate2::driveWheels(int right, int left){
	clamp(right, -500, 500);
	clamp(left, -500, 500);
	if (usingSoftSerial){
		softSerial.write(145);
		softSerial.write(right & 0x7F);
		softSerial.write((right >> 7) & 0x7F);
		softSerial.write(left & 0x7F);
		softSerial.write((left >> 7) & 0x7F);
	}
	else {
		softSerial.write(145);
		softSerial.write(right & 0x7F);
		softSerial.write((right >> 7) & 0x7F);
		softSerial.write(left & 0x7F);
		softSerial.write((left >> 7) & 0x7F);
	}
}
void iRobotCreate2::driveLeft(int left){
	driveWheels(left, 0);
}
void iRobotCreate2::driveRight(int right){
	driveWheels(0, right);
}
void iRobotCreate2::driveWheelsPWM(int rightPWM, int leftPWM){
	clamp(rightPWM, -255, 255);
	clamp(leftPWM, -255, 255);
	if (usingSoftSerial){
		softSerial.write(146);
		softSerial.write(rightPWM & 0x7F);
		softSerial.write((rightPWM >> 7) & 0x7F);
		softSerial.write(leftPWM & 0x7F);
		softSerial.write((leftPWM >> 7) & 0x7F);
	}
	else {
		softSerial.write(146);
		softSerial.write(rightPWM & 0x7F);
		softSerial.write((rightPWM >> 7) & 0x7F);
		softSerial.write(leftPWM & 0x7F);
		softSerial.write((leftPWM >> 7) & 0x7F);
	}
}
//cleaning motors
void iRobotCreate2::enableBrushes(bool mainBrushDirection, bool sideBrushDirection, bool mainBrush, bool vacuum, bool sideBrush){

	byte motorsEnabled = (mainBrushDirection ? 16 : 0) + (sideBrushDirection ? 8 : 0) + (mainBrush ? 4 : 0) + (vacuum ? 2 : 0) + (sideBrush ? 1 : 0);
	if (usingSoftSerial){
		softSerial.write(138);
		softSerial.write(motorsEnabled);
	}
	else {
		Serial.write(138);
		Serial.write(motorsEnabled);
	}
}
void iRobotCreate2::setMainBrush(bool direction, bool enable){
	enableBrushes(direction, _sideBrushDirection, enable, _vacuum, _sideBrush);
}
void iRobotCreate2::setSideBrush(bool direction, bool enable){
	enableBrushes(_mainBrushDirection, direction, _mainBrush, _vacuum, enable);
}
void iRobotCreate2::enableVacuum(bool enable){
	enableBrushes(_mainBrushDirection, _sideBrushDirection, _mainBrush, enable, _sideBrush);
}
void iRobotCreate2::setMainBrushSpeed(char speed){
	_mainBrushSpeed = speed;
	if (usingSoftSerial){
		softSerial.write(144);
		softSerial.write((byte)speed);
		softSerial.write((byte)_sideBrushSpeed);
		softSerial.write((byte)_vacuumSpeed);
	}
	else {
		Serial.write(144);
		Serial.write((byte)speed);
		Serial.write((byte)_sideBrushSpeed);
		Serial.write((byte)_vacuumSpeed);
	}
}
void iRobotCreate2::setSideBrushSpeed(char speed){
	_sideBrushSpeed = speed;
	if (usingSoftSerial){
		softSerial.write(144);
		softSerial.write((byte)_mainBrushSpeed);
		softSerial.write((byte)speed);
		softSerial.write((byte)_vacuumSpeed);
	}
	else {
		Serial.write(144);
		Serial.write((byte)_mainBrushSpeed);
		Serial.write((byte)speed);
		Serial.write((byte)_vacuumSpeed);
	}
}
void iRobotCreate2::setVaccumSpeed(char speed){
	_vacuumSpeed = speed;
	if (usingSoftSerial){
		softSerial.write(144);
		softSerial.write((byte)_mainBrushSpeed);
		softSerial.write((byte)_sideBrushSpeed);
		softSerial.write((byte)speed);
	}
	else {
		Serial.write(144);
		Serial.write((byte)_mainBrushSpeed);
		Serial.write((byte)_sideBrushSpeed);
		Serial.write((byte)speed);
	}
}
//leds
void iRobotCreate2::setPowerLEDs(byte color, byte intensity){
	_color = color;
	_intensity = intensity;
	if (usingSoftSerial){
		softSerial.write(139);
		softSerial.write((byte)0x00);
		softSerial.write((byte)_color);
		softSerial.write((byte)_intensity);
	}
	else {
		Serial.write(139);
		Serial.write((byte)0x00);
		Serial.write((byte)_color);
		Serial.write((byte)_intensity);
	}
}
void iRobotCreate2::setDebrisLED(bool enable){
	_debrisLED = enable;
	if (usingSoftSerial){
		softSerial.write(139);
		softSerial.write((_debrisLED ? 1 : 0) + (_spotLED ? 2 : 0) + (_dockLED ? 4 : 0) + (_warningLED ? 8 : 0));
		softSerial.write((byte)_color);
		softSerial.write((byte)_intensity);
	}
	else {
		Serial.write(139);
		Serial.write((_debrisLED ? 1 : 0) + (_spotLED ? 2 : 0) + (_dockLED ? 4 : 0) + (_warningLED ? 8 : 0));
		Serial.write((byte)_color);
		Serial.write((byte)_intensity);
	}
}
void iRobotCreate2::setSpotLED(bool enable){
	_spotLED = enable;
	if (usingSoftSerial){
		softSerial.write(139);
		softSerial.write((_debrisLED ? 1 : 0) + (_spotLED ? 2 : 0) + (_dockLED ? 4 : 0) + (_warningLED ? 8 : 0));
		softSerial.write((byte)_color);
		softSerial.write((byte)_intensity);
	}
	else {
		Serial.write(139);
		Serial.write((_debrisLED ? 1 : 0) + (_spotLED ? 2 : 0) + (_dockLED ? 4 : 0) + (_warningLED ? 8 : 0));
		Serial.write((byte)_color);
		Serial.write((byte)_intensity);
	}
}
void iRobotCreate2::setDockLED(bool enable){
	_dockLED = enable;
	if (usingSoftSerial){
		softSerial.write(139);
		softSerial.write((_debrisLED ? 1 : 0) + (_spotLED ? 2 : 0) + (_dockLED ? 4 : 0) + (_warningLED ? 8 : 0));
		softSerial.write((byte)_color);
		softSerial.write((byte)_intensity);
	}
	else {
		Serial.write(139);
		Serial.write((_debrisLED ? 1 : 0) + (_spotLED ? 2 : 0) + (_dockLED ? 4 : 0) + (_warningLED ? 8 : 0));
		Serial.write((byte)_color);
		Serial.write((byte)_intensity);
	}
}
void iRobotCreate2::setWarningLED(bool enable){
	_warningLED = enable;
	if (usingSoftSerial){
		softSerial.write(139);
		softSerial.write((_debrisLED ? 1 : 0) + (_spotLED ? 2 : 0) + (_dockLED ? 4 : 0) + (_warningLED ? 8 : 0));
		softSerial.write((byte)_color);
		softSerial.write((byte)_intensity);
	}
	else {
		Serial.write(139);
		Serial.write((_debrisLED ? 1 : 0) + (_spotLED ? 2 : 0) + (_dockLED ? 4 : 0) + (_warningLED ? 8 : 0));
		Serial.write((byte)_color);
		Serial.write((byte)_intensity);
	}
}
void iRobotCreate2::setScheduleLEDs(byte days, bool schedule, bool clock, bool am, bool pm, bool colon){
	if (usingSoftSerial){
		softSerial.write(162);
		softSerial.write(days);
		softSerial.write((colon ? 1 : 0) + (pm ? 2 : 0) + (am ? 4 : 0) + (clock ? 8 : 0) + (schedule ? 16 : 0));
	}
	else {
		Serial.write(162);
		Serial.write(days);
		Serial.write((colon ? 1 : 0) + (pm ? 2 : 0) + (am ? 4 : 0) + (clock ? 8 : 0) + (schedule ? 16 : 0));
	}
}
void iRobotCreate2::setDigitLEDs(byte digit1, byte digit2, byte digit3, byte digit4){
	if (usingSoftSerial){
		softSerial.write(163);
		softSerial.write(digit1);
		softSerial.write(digit2);
		softSerial.write(digit3);
		softSerial.write(digit4);
	}
	else {
		Serial.write(163);
		Serial.write(digit1);
		Serial.write(digit2);
		Serial.write(digit3);
		Serial.write(digit4);
	}
}
void iRobotCreate2::setDigitLEDFromASCII(byte digit, char letter){
	switch (digit){
	case 1:
		_digit1 = letter;
		break;
	case 2:
		_digit2 = letter;
		break;
	case 3:
		_digit3 = letter;
		break;
	case 4:
		_digit4 = letter;
		break;
	}
	if (usingSoftSerial){
		softSerial.write(164);
		softSerial.write(_digit1);
		softSerial.write(_digit2);
		softSerial.write(_digit3);
		softSerial.write(_digit4);
	}
	else {
		Serial.write(164);
		Serial.write(digit);
		Serial.write(_digit1);
		Serial.write(_digit2);
		Serial.write(_digit3);
		Serial.write(_digit4);
	}
}

//non blocking sensor functions, serial data has to be decrypted outside of library or in separate function
void iRobotCreate2::requestSensorData(byte sensorID) {
	byte packetID = 0;
	if (sensorID > 100){
		switch (sensorID){
		case 101:
		case 102:
		case 103:
		case 104:
			packetID = 7;
			break;
		case 105:
		case 106:
		case 107:
		case 108:
			packetID = 14;
			break;
		case 109:
		case 110:
		case 111:
		case 112:
		case 113:
		case 114:
		case 115:
		case 116:
			packetID = 18;
			break;
		case 117:
		case 118:
		case 119:
		case 120:
		case 121:
		case 122:
			packetID = 45;
			break;
		}

	}
	else {
		packetID = sensorID;
	}
	if (usingSoftSerial){
		softSerial.write(142);
		softSerial.write(packetID);
	}
	else {
		Serial.write(142);
		Serial.write(packetID);
	}

}
void iRobotCreate2::requestSensorDataList(byte numOfRequests, byte requestIDs[]) {
	byte packetIDs[numOfRequests];
	for (int i = 0; i<numOfRequests; i++){
		if (requestIDs[i] > 100){
			switch (requestIDs[i]){
			case 101:
			case 102:
			case 103:
			case 104:
				packetIDs[i] = 7;
				break;
			case 105:
			case 106:
			case 107:
			case 108:
				packetIDs[i] = 14;
				break;
			case 109:
			case 110:
			case 111:
			case 112:
			case 113:
			case 114:
			case 115:
			case 116:
				packetIDs[i] = 18;
				break;
			case 117:
			case 118:
			case 119:
			case 120:
			case 121:
			case 122:
				packetIDs[i] = 45;
				break;
			}

		}
		else {
			packetIDs[i] = requestIDs[i];
		}
	}
	if (usingSoftSerial){
		softSerial.write(149);
		softSerial.write(numOfRequests);
		for (int i = 0; i < numOfRequests; i++){
			softSerial.write(packetIDs[i]);
		}
	}
	else {
		Serial.write(149);
		Serial.write(numOfRequests);
		for (int i = 0; i < numOfRequests; i++){
			Serial.write(packetIDs[i]);
		}
	}

}
void iRobotCreate2::beginDataStream(byte numOfRequests, byte requestIDs[]){
	byte packetIDs[numOfRequests];
	for (int i = 0; i<numOfRequests; i++){
		if (requestIDs[i] > 100){
			switch (requestIDs[i]){
			case 101:
			case 102:
			case 103:
			case 104:
				packetIDs[i] = 7;
				break;
			case 105:
			case 106:
			case 107:
			case 108:
				packetIDs[i] = 14;
				break;
			case 109:
			case 110:
			case 111:
			case 112:
			case 113:
			case 114:
			case 115:
			case 116:
				packetIDs[i] = 18;
				break;
			case 117:
			case 118:
			case 119:
			case 120:
			case 121:
			case 122:
				packetIDs[i] = 45;
				break;
			}

		}
		else {
			packetIDs[i] = requestIDs[i];
		}
	}
	if (usingSoftSerial){
		softSerial.write(148);
		softSerial.write(numOfRequests);
		for (int i = 0; i < numOfRequests; i++){
			softSerial.write(packetIDs[i]);
		}
	}
	else {
		Serial.write(148);
		Serial.write(numOfRequests);
		for (int i = 0; i < numOfRequests; i++){
			Serial.write(packetIDs[i]);
		}
	}

}
void iRobotCreate2::pauseStream(){
	if (usingSoftSerial){
		softSerial.write(150);
		softSerial.write((byte)0x00);
	}
	else {
		Serial.write(150);
		Serial.write((byte)0x00);
	}
}
void iRobotCreate2::resumeSteam(){
	if (usingSoftSerial){
		softSerial.write(150);
		softSerial.write(1);
	}
	else {
		Serial.write(150);
		Serial.write(1);
	}
}

//blocking sensor functions - these will request data and wait until a response is recieved, then return the response
int iRobotCreate2::getSensorData(byte sensorID){
	int returnVal;
	byte packetID = 0;
	if (sensorID > 100){
		switch (sensorID){
		case 101:
		case 102:
		case 103:
		case 104:
			packetID = 7;
			break;
		case 105:
		case 106:
		case 107:
		case 108:
			packetID = 14;
			break;
		case 109:
		case 110:
		case 111:
		case 112:
		case 113:
		case 114:
		case 115:
		case 116:
			packetID = 18;
			break;
		case 117:
		case 118:
		case 119:
		case 120:
		case 121:
		case 122:
			packetID = 45;
			break;
		}

	}
	else {
		packetID = sensorID;
	}
	byte MSB = 0;
	byte LSB = 0;
	if (usingSoftSerial){
		softSerial.write(142);
		softSerial.write(packetID);
		while (softSerial.available()){
			MSB = softSerial.read();
			LSB = softSerial.read();

		}
	}
	else {
		Serial.write(142);
		Serial.write(packetID);
		while (Serial.available()){
			MSB = Serial.read();
			LSB = Serial.read();
		}
	}
	returnVal = (MSB << 7) | LSB;
	return returnVal;
}
int * iRobotCreate2::getSensorData(byte numOfRequests, byte requestIDs[]){
	int returnVal[numOfRequests];
	byte packetIDs[numOfRequests];
	for (int i = 0; i<numOfRequests; i++){
		if (requestIDs[i] > 100){
			switch (requestIDs[i]){
			case 101:
			case 102:
			case 103:
			case 104:
				packetIDs[i] = 7;
				break;
			case 105:
			case 106:
			case 107:
			case 108:
				packetIDs[i] = 14;
				break;
			case 109:
			case 110:
			case 111:
			case 112:
			case 113:
			case 114:
			case 115:
			case 116:
				packetIDs[i] = 18;
				break;
			case 117:
			case 118:
			case 119:
			case 120:
			case 121:
			case 122:
				packetIDs[i] = 45;
				break;
			}

		}
		else {
			packetIDs[i] = requestIDs[i];
		}
	}
	if (usingSoftSerial){
		softSerial.write(149);
		softSerial.write(numOfRequests);
		for (int i = 0; i < numOfRequests; i++){
			softSerial.write(packetIDs[i]);
		}
	}
	else {
		Serial.write(149);
		Serial.write(numOfRequests);
		for (int i = 0; i < numOfRequests; i++){
			Serial.write(packetIDs[i]);
		}
	}
	byte MSB = 0;
	byte LSB = 0;
	if (usingSoftSerial){
		while (softSerial.available()){
			MSB = softSerial.read();
			LSB = softSerial.read();

		}
	}
	else {
		while (Serial.available()){
			MSB = Serial.read();
			LSB = Serial.read();
		}
	}

	return returnVal;
}

void iRobotCreate2::getSensorData(byte * buffer, byte bufferLength)
{
	while (bufferLength-- > 0)
	{
		unsigned long startTime = millis();
		if (usingSoftSerial){
			while (!softSerial->available())
			{
				// Look for a timeout
				if (millis() > startTime + 200)
					return false; // Timed out
			}
			*buffer++ = softSerial.read();
		}
		else {
			while (!Serial->available())
			{
				// Look for a timeout
				if (millis() > startTime + 200)
					return false; // Timed out
			}
			*buffer++ = Serial.read();
		}
	}
}