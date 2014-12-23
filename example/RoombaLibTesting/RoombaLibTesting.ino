#include <iRobotCreate2.h>

iRobotCreate2 roomba(true, 10,7,3);

/*
* RX connect to TX of other device
* TX connect to RX of other device
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
*/

int totalDuration1 =0;
int totalDuration2 =0;
int totalDuration3 =0;


void setup(){
  Serial.begin(9600);
  //roomba.resetBaudRate();
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
  songNotes[0].note = 76;
  songNotes[1].note = 76;
  songNotes[2].note = 76;
  songNotes[3].note = 76;
  songNotes[4].note = 76;
  songNotes[5].note = 76;
  songNotes[6].note = 76;
  songNotes[7].note = 79;
  songNotes[8].note = 72;
  songNotes[9].note = 74;
  songNotes[10].note = 76;
  
  
  songNotes[0].duration = 16;
  songNotes[1].duration = 16;
  songNotes[2].duration = 32;
  songNotes[3].duration = 16;
  songNotes[4].duration = 16;
  songNotes[5].duration = 32;
  songNotes[6].duration = 16;
  songNotes[7].duration = 16;
  songNotes[8].duration = 16;
  songNotes[9].duration = 16;
  songNotes[10].duration = 64;
  
  roomba.createSong(1, 11, songNotes);
  
  for(int i=0;i<11;i++){
    totalDuration1 += songNotes[i].duration;
  }
  roomba.playSong(1);
  totalDuration1 = 100+1000*(totalDuration1/64.0);
  delay(totalDuration1);
   
  songNotes[0].note = 77;
  songNotes[1].note = 77;
  songNotes[2].note = 77;
  songNotes[3].note = 77;
  songNotes[4].note = 77;
  songNotes[5].note = 76;
  songNotes[6].note = 76;
  songNotes[7].note = 76;
  songNotes[8].note = 76;
  songNotes[9].note = 74;
  songNotes[10].note = 74;
  songNotes[11].note = 76;
  songNotes[12].note = 74;
  songNotes[13].note = 79;
  
  
  songNotes[0].duration = 16;
  songNotes[1].duration = 16;
  songNotes[2].duration = 16;
  songNotes[3].duration = 16;
  songNotes[4].duration = 16;
  songNotes[5].duration = 16;
  songNotes[6].duration = 16;
  songNotes[7].duration = 16;
  songNotes[8].duration = 16;
  songNotes[9].duration = 16;
  songNotes[10].duration = 16;
  songNotes[11].duration = 16;
  songNotes[12].duration = 32;
  songNotes[13].duration = 32;
  
  roomba.createSong(2, 14, songNotes);
  
  for(int i=0;i<14;i++){
    totalDuration2 += songNotes[i].duration;
  }
  
  roomba.playSong(2);
  totalDuration2 = 100+1000*(totalDuration2/64.0);
  delay(totalDuration2);
  
  roomba.playSong(1);
  delay(totalDuration1);
  
  songNotes[0].note = 77;
  songNotes[1].note = 77;
  songNotes[2].note = 77;
  songNotes[3].note = 77;
  songNotes[4].note = 77;
  songNotes[5].note = 76;
  songNotes[6].note = 76;
  songNotes[7].note = 76;
  songNotes[8].note = 79;
  songNotes[9].note = 79;
  songNotes[10].note = 76;
  songNotes[11].note = 74;
  songNotes[12].note = 72;
  
  
  songNotes[0].duration = 16;
  songNotes[1].duration = 16;
  songNotes[2].duration = 16;
  songNotes[3].duration = 16;
  songNotes[4].duration = 16;
  songNotes[5].duration = 16;
  songNotes[6].duration = 16;
  songNotes[7].duration = 16;
  songNotes[8].duration = 16;
  songNotes[9].duration = 16;
  songNotes[10].duration = 16;
  songNotes[11].duration = 16;
  songNotes[12].duration = 64;
  
  roomba.createSong(3, 13, songNotes);
  
  for(int i=0;i<13;i++){
    totalDuration3 += songNotes[i].duration;
  }
  
  roomba.playSong(3);
  totalDuration3 = 100+1000*(totalDuration3/64.0);
  delay(totalDuration3);
  //roomba.pushButton(Clean + Minute + Hour);
  
  //roomba.drive(100, 0);
  //delay(1000);
  //roomba.driveLeft(200);
  //delay(1000);
  //roomba.driveRight(200);
  //delay(1000);
  //roomba.drive(0,0);
  
//  delay(17000);
 // roomba.turnOff();
roomba.clean();

}

void loop(){
  delay(600000);
  roomba.fullMode();
  delay(2000);
  roomba.playSong(1);
  delay(totalDuration1);
  roomba.playSong(2);
  delay(totalDuration2);
  roomba.playSong(1);
  delay(totalDuration1);
  roomba.playSong(3);
  delay(totalDuration3);
  delay(3000);
  roomba.clean();
}


