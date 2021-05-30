#include <Servo.h>

#define yellowLED 12
#define redLED 11
#define blueLED 10
#define greenLED 9

#define yellowREAD A2
#define redREAD A5
#define blueREAD A3
#define greenREAD A0

#define PINservoNS 5
#define PINservoEV 6

#define servoInitalValueNS 90
#define servoInitalValueEV 90

#define activateValue 200

#define loopDelay 0
#define servoDelay 20

#define lowerAngleBoundry 40
#define upperAngleBoundry 120

Servo servoNS;
Servo servoEV;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  pinMode(yellowREAD, INPUT);
  pinMode(redREAD, INPUT);
  pinMode(blueREAD, INPUT);
  pinMode(greenREAD, INPUT);

  servoNS.attach(PINservoNS);
  servoEV.attach(PINservoEV);

  servoNS.write(servoInitalValueNS);
  delay(500);
  servoEV.write(servoInitalValueEV);
  delay(500);
  

  
}





void loop() {

  int yellowStatus = analogRead(yellowREAD);
  int redStatus = analogRead(redREAD);
  int blueStatus = analogRead(blueREAD);
  int greenStatus = analogRead(greenREAD);

  printSerial(yellowStatus, redStatus, blueStatus, greenStatus);
  servoControl(yellowStatus, redStatus, blueStatus, greenStatus);

  delay(loopDelay);
  
}

void servoControl(int yellowStatus, int redStatus, int blueStatus, int greenStatus) {

  static int NSpos = servoInitalValueNS;
  static int EVpos = servoInitalValueEV;

  #define yellowREAD A2
  #define redREAD A5
  #define blueREAD A3
  #define greenREAD A0

  
  int northSensor = blueStatus;
  int southSensor = yellowStatus;
  
  int eastSensor = greenStatus;
  int westSensor = redStatus;

  
  int NSDif = northSensor - southSensor;
  int EVDif = eastSensor - westSensor;

  int NSDelta = 0;
  int EVDelta = 0;
  
  if(abs(NSDif) > activateValue){
    /*
      North has greater value than south, so move south
    */
    if(NSDif > 0){
      NSDelta = -1;
    }
    else{
      NSDelta = 1;
    }
  }

  if(abs(EVDif) > activateValue){
    /*
      North has greater value than south, so move south
    */
    if(EVDif > 0){
      EVDelta = -1;
    }
    else{
      EVDelta = 1;
    }
  }
  

  //Value checks so I don't damage the servo motor
  if((lowerAngleBoundry <= (NSpos + NSDelta)) && ((NSpos + NSDelta) <= upperAngleBoundry)) {
    //do stuff to NS servomotor 
    NSpos += NSDelta;
    servoNS.write(NSpos);
    delay(servoDelay);
  }

  Serial.println("Move NS " + String(NSpos));
  
  if((lowerAngleBoundry <= (EVpos + EVDelta)) && ((EVpos + EVDelta) <= upperAngleBoundry)) {
    //do stuff to EV servomotor 
    EVpos += EVDelta;
    servoEV.write(EVpos);
    delay(servoDelay);
  }

  Serial.println("Move EV " + String(EVpos));
  
  
}

void printSerial(int yellowStatus, int redStatus, int blueStatus, int greenStatus) {
  String yellowMessage = "yellow " + String(yellowStatus, DEC);
  Serial.println(yellowMessage);

  String redMessage = "red " + String(redStatus, DEC);
  Serial.println(redMessage);

  String blueMessage = "blue " + String(blueStatus, DEC);
  Serial.println(blueMessage);

  String greenMessage = "green " + String(greenStatus, DEC);
  Serial.println(greenMessage);
}
