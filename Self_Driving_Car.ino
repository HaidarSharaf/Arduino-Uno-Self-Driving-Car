#include <AFMotor.h>
#include <Servo.h> 

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
Servo servo;

const int SPEED = 160;  

void setup() {
  Serial.begin(9600);
  motor1.setSpeed(SPEED);
  motor2.setSpeed(SPEED);
  motor3.setSpeed(SPEED);
  motor4.setSpeed(SPEED);
  servo.attach(90);  
  pinMode(A2, OUTPUT);
  pinMode(A1, INPUT);
}
 
void loop() {
  moveForward();
  double disF=readUltrasonicDistance(A2, A1);
  if(disF>=2 && disF<=15){
    Stop();
    delay(1000);
    moveBackwards();
    Stop();
    delay(1000);
    servo.write(180);
    double disR=readUltrasonicDistance(A2, A1);
    delay(500);
    servo.write(0);
    double disL=readUltrasonicDistance(A2, A1);
    delay(500);              
    if(disR>disL){
      moveRight();
    }
    else{
      moveLeft();
    }
  }
}

void moveForward(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackwards(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(600);
}

void moveRight(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(1000);
}

void moveLeft(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(1000);
}

void Stop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

int readUltrasonicDistance(int triggerPin, int echoPin){
  int distance;
  digitalWrite(triggerPin, LOW);
  delay(30);
  digitalWrite(triggerPin, HIGH);
  delay(30);
  digitalWrite(triggerPin, LOW);
  distance = pulseIn(echoPin, HIGH)/2/29;
  return distance;
}
