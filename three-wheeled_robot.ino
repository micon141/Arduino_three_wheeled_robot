#include<Servo.h>

//Pins:
int in1=9;
int in2=8;
int in3=7;
int in4=6;
int enA=10;
int enB=5;
int servoPin=0;
int trigPin=1;
int echoPin=2;
float distance=5.0;
float sensorDistance;
float speedOfSound=343.0;

Servo myservo;

void setup() {

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  myservo.attach(servoPin);
  myservo.write(90);
  delay(700);
  
}

void loop() {

  sensorDistance = measureDistance();

  if (sensorDistance > distance) {
    forward();
  }
  if (sensorDistance <= distance) {
    findroute();
  }

}

void forward() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void findroute() {
  stopmotor();
  
  if (leftDistance() > rightDistance()) {
    goleft();
  }
  else {
    goright();
  }
  
}

void stopmotor() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(500);
}

float measureDistance() {
  float d;
  float pingTime;
  
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(15);

  pingTime = pulseIn(echoPin,HIGH);
  pingTime = pingTime/1000000.;
  d = speedOfSound*pingTime/2.0;
  d = d*100;                       
  return d;
}

float leftDistance() {
  myservo.write(20);
  delay(700);
  float d = measureDistance();
  myservo.write(90);
  delay(700);
  return d;
}

float rightDistance() {
  myservo.write(170);
  delay(700);
  float d = measureDistance();
  myservo.write(90);
  delay(700);
  return d;
}

void goleft() {
  //Right wheel - forward, Left wheel - backward
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1000);
  stopmotor();
}

void goright() {
  //Right wheel - backward, Left wheel - forward
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(1000);
  stopmotor();
}
