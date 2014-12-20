#include <iRobotCreate2.h>

iRobotCreate2 roomba(true, 6,7,3);

void setup(){
  Serial.begin(9600);
  ///roomba.resetBaudRate();
  delay(2000);
  roomba.start();
  roomba.fullMode();
  delay(1000);
  roomba.setPowerLEDs(128, 128);
  roomba.setDebrisLED(true);
  roomba.setSpotLED(true);
  roomba.setDockLED(true);
  roomba.setWarningLED(true);
  roomba.setScheduleLEDs(Monday + Wednesday, true, true, true, false, true);
  roomba.setDigitLEDFromASCII(1, 'A');
  roomba.setDigitLEDFromASCII(2, 'B');
  roomba.setDigitLEDFromASCII(3, 'C');
  roomba.setDigitLEDFromASCII(4, 'D');
  
  Notes songNotes[16];
  songNotes[0].note = 57;
  songNotes[1].note = 59;
  songNotes[2].note = 60;
  songNotes[3].note = 62;
  songNotes[4].note = 64;
  songNotes[5].note = 65;
  songNotes[6].note = 67;
  songNotes[7].note = 69;
  songNotes[8].note = 71;
  songNotes[9].note = 72;
  songNotes[10].note = 74;
  songNotes[11].note = 76;
  songNotes[12].note = 77;
  songNotes[13].note = 79;
  songNotes[14].note = 81;
  songNotes[15].note = 83;
  for(int i=0;i<16;i++){
   songNotes[i].duration = 64; 
  }
  roomba.createSong(1, 16, songNotes);
  roomba.playSong(1);
  
  //roomba.pushButton(Clean + Minute + Hour);
  
  roomba.drive(100, 0);
  delay(1000);
  roomba.driveLeft(200);
  delay(1000);
  roomba.driveRight(200);
  delay(1000);
  roomba.drive(0,0);
  
  delay(17000);
  roomba.turnOff();
}

void loop(){
  
}


