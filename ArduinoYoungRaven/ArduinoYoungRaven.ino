#include "CytronMotorDriver.h" 

int frPWM = 12;
int frDIR = 11;
int frEA = 2;
int frEB = 3;
int flPWM = 15;
int flDIR = 14;
int flEA = 6;
int flEB = 7;
int brPWM = 1;
int brDIR = 0;
int bfrEA = 10;
int brEB = 11;
int blPWM = 3;
int blDIR = 2;
int blEA = 14;
int blEB = 15;

int joyX;
int joyY;
int joyR;

int front_left = 0;
int rear_left = 0;
int front_right = 0;
int rear_right = 0;

float volt = 0;
long timeer = 0;
long oldMills = 0;
int ledState = 0;

#define FORWARD 255
#define REVERSE -255
#define NEUTRAL 0
CytronMD FrontRight(PWM_DIR, frPWM, frDIR);
CytronMD FrontLeft(PWM_DIR, flPWM, flDIR);
CytronMD BackRight(PWM_DIR, brPWM, brDIR);
CytronMD BackLeft(PWM_DIR, blPWM, blDIR);


void setup() {
  Serial.begin(115200);  
  pinMode(26, INPUT);
  pinMode(25, OUTPUT);
}

int maximum (int motor) {
  if (motor > FORWARD) {
   return motor = FORWARD;
  }else if (motor < REVERSE){
    return motor = REVERSE;
  }else {
    return motor;
}
}
void debug(){
  Serial.print(maximum(front_left));
  Serial.print("\t");
  Serial.println(maximum(front_right));
  Serial.print(maximum(rear_left));
  Serial.print("\t");
  Serial.println(maximum(rear_right));
  Serial.println(volt);
  Serial.println(ledState);
}
void loop() {
  if (Serial.available() > 1) {
    byte data = Serial.read();
    if (data == 'x') {
      int tmp = Serial.parseInt();
      joyX = tmp;                 //joystick input from -255 to 255
    }
    if (data == 'y') {
      int tmp = Serial.parseInt();
      joyY=tmp;
    }
    if (data == 'r'){
      int tmp=Serial.parseInt();
      joyR=tmp;
    }
  }
int drive =  joyY - NEUTRAL;
int strafe = joyX - NEUTRAL;
int rotate = joyR - NEUTRAL;

volt = analogRead(26);

timeer = map(volt, 750, 1024, 1, 1500);

if(millis()-oldMills > timeer){
    if (ledState == 0){
      ledState=1;
    }
    else{
      ledState=0;
    }
    digitalWrite(25, ledState);
    oldMills = millis();
}

front_left = drive + strafe + rotate;
rear_left = drive - strafe + rotate ;
front_right = drive - strafe - rotate;
rear_right = drive + strafe - rotate;
FrontRight.setSpeed(front_right);
FrontLeft.setSpeed(-front_left);
BackRight.setSpeed(rear_right);
BackLeft.setSpeed(-rear_left);

debug();
}