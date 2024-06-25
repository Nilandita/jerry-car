#include <Servo.h>
#include <AFMotor.h>
#include <NewPing.h>
#define Echo A4
#define Trig A3
#define motor 10
#define Speed 140
#define spoint 103
#define maximum_distance 200
NewPing sonar(Trig,Echo,maximum_distance); 
char value;
int distance=100;
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;
Servo servo;
AF_DCMotor fl(1);
AF_DCMotor bl(4);
AF_DCMotor fr(2);
AF_DCMotor br(3);

void setup() 
{
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(motor);
  fl.setSpeed(Speed);
  bl.setSpeed(Speed);
  fr.setSpeed(Speed);
  br.setSpeed(Speed);

  servo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();                                                    
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}
void loop() {
   Obstacle();
    //Bluetoothcontrol();
   //voicecontrol();
}
void Bluetoothcontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
  }
  if (value == 'F') {
    forward();
  } else if (value == 'B') {
    backward();
  } else if (value == 'L') {
    left();
  } else if (value == 'R') {
    right();
  } else if (value == 'S') {
    Stop();
  }
  else if (value == 'G') {
    forward();
    left();
  }
  else if (value == 'I') {
    forward();
    right();
  }
  else if (value == 'H') {
    backward();
    left();
  }
  else if (value == 'J') {
    backward();
    right();
  }
  else if (value=='0')
  {
  fl.setSpeed(Speed);
  bl.setSpeed(Speed);
  fr.setSpeed(Speed);
  br.setSpeed(Speed);
  }
    else if (value=='5')
  {
  fl.setSpeed(200);
  bl.setSpeed(200);
  fr.setSpeed(200);
  br.setSpeed(200);
  }
  else if (value=='9')
  {
  fl.setSpeed(300);
  bl.setSpeed(300);
  fr.setSpeed(300);
  br.setSpeed(300);
  }
}
void Obstacle() {
   int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  if (distance <= 45){
    Stop();
    delay(300);
    backward();
    delay(900);
    Stop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);
    if (distanceRight >= distanceLeft){
      right();
      //Stop();
    }
    else{
      left();
      //Stop();
    }
  }
  else{
    forward();
  }
    distance = readPing();


  // distance = ultrasonic();
  // if (distance <= 12) {
  //   Stop();
  //   backward();
  //   delay(100);
  //   Stop();
  //   L = leftsee();
  //   servo.write(spoint);
  //   delay(800);
  //   R = rightsee();
  //   servo.write(spoint);
  //   if (L < R) {
  //     right();
  //     delay(500);
  //     Stop();
  //     delay(200);
  //   } else if (L > R) {
  //     left();
  //     delay(500);
  //     Stop();
  //     delay(200);
  //   }
  // } else {
  //   forward();
  // }
}

int lookRight(){

  servo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo.write(115);
  return distance;
}
int lookLeft(){
   
  servo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo.write(115);
  return distance;
  delay(100);
}
int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}
void voicecontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
    if (value == '^') {
      forward();
    } else if (value == '-') {
      backward();
    } else if (value == '<') {
      L = lookLeft();
      servo.write(spoint);
      if (L >= 10 ) {
        left();
        delay(500);
        Stop();
      } else if (L < 10) {
        Stop();
      }
    } else if (value == '>') {
      R = lookRight();
      servo.write(spoint);
      if (R >= 10 ) {
        right();
        delay(500);
        Stop();
      } else if (R < 10) {
        Stop();
      }
    } else if (value == '*') {
      Stop();
    }
  }
}
// Ultrasonic sensor distance reading function
// int ultrasonic() {
//   digitalWrite(Trig, LOW);
//   delayMicroseconds(4);
//   digitalWrite(Trig, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(Trig, LOW);
//   long t = pulseIn(Echo, HIGH);
//   long cm = t / 29 / 2; //time convert distance
//   return cm;
// }
void forward() {
  fl.run(FORWARD);
  bl.run(FORWARD);
  fr.run(FORWARD);
  br.run(FORWARD);
}
void backward() {
  fl.run(BACKWARD);
  bl.run(BACKWARD);
  fr.run(BACKWARD);
  br.run(BACKWARD);
}
void right() {
  fl.run(FORWARD);
  bl.run(FORWARD);
  fr.run(BACKWARD);
  br.run(BACKWARD);
}
void left() {
  fl.run(BACKWARD);
  bl.run(BACKWARD);
  fr.run(FORWARD);
  br.run(FORWARD);
}
void Stop() {
  fl.run(RELEASE);
  bl.run(RELEASE);
  fr.run(RELEASE);
  br.run(RELEASE);
}
// int rightsee() {
//   servo.write(20);
//   delay(800);
//   Left = ultrasonic();
//   return Left;
// }
// int leftsee() {
//   servo.write(180);
//   delay(800);
//   Right = ultrasonic();
//   return Right;
// }