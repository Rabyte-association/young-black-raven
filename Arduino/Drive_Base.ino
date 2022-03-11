#define rightFrontPower 11
#define rightFrontDir 12 
#define leftFrontPower 10 
#define leftFrontDir 9
#define rightBackPower 6 
#define rightBackDir 7
#define leftBackPower 5
#define leftBackDir 4

void rightFront(uint8_t power, bool dir){
  digitalWrite(rightFrontDir,dir);
  analogWrite(rightFrontPower, power);
}

void leftFront(uint8_t power, bool dir){
  digitalWrite(leftFrontDir,!dir);
  analogWrite(leftFrontPower, power);
}

void rightBack(uint8_t power, bool dir){
  digitalWrite(rightBackDir,dir);
  analogWrite(rightBackPower, power);
}
void leftBack(uint8_t power, bool dir){
  digitalWrite(leftBackDir,!dir);
  analogWrite(leftBackPower, power);
}

void moveForward(uint8_t power, uint64_t duration){
  rightFront(power,true);
  leftFront(power,true);
  rightBack(power,true);
  leftBack(power,true);
  delay(duration);
}

void moveBackward(uint8_t power, uint64_t duration){
  rightFront(power,false);
  leftFront(power,false);
  rightBack(power,false);
  leftBack(power,false);
  delay(duration);
}

void moveRight(uint8_t power, uint64_t duration){
  rightFront(power,false);
  leftFront(power,true);
  rightBack(power,true);
  leftBack(power,false);
  delay(duration);
}

void moveLeft(uint8_t power, uint64_t duration){
  rightFront(power,true);
  leftFront(power,false);
  rightBack(power,false);
  leftBack(power,true);
  delay(duration);
}
void stopMotors(){
  rightFront(0,true);
  leftFront(0,true);
  rightBack(0,true);
  leftBack(0,true);
}

void setup() {
  pinMode(rightFrontPower, OUTPUT);
  pinMode(rightFrontDir, OUTPUT);
  pinMode(leftFrontPower, OUTPUT);
  pinMode(leftFrontDir, OUTPUT);
  pinMode(rightBackPower, OUTPUT);
  pinMode(rightBackDir, OUTPUT);
  pinMode(leftBackPower, OUTPUT);
  pinMode(leftBackDir, OUTPUT);
}

 
void loop() {
  delay(10000);
  moveForward(50,2000);
  moveRight(50,2000);
  moveBackward(50,2000);
  moveLeft(50,2000);
  stopMotors();
  delay(10000);
  
}
