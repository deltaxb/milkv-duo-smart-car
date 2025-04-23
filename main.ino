#include "motor.h"

void setup() {
  Serial.begin(115200);
  //stop_motor();
}
/*
void stop_left_motor() {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACK, LOW);
  analogWrite(LEFT_SPEED, 0);
}

void stop_right_motor() {
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACK, LOW);
  analogWrite(RIGHT_SPEED, 0);
}

void stop_motor() {
  stop_left_motor();
  stop_right_motor();
}

const int DEFAULT_SPEED = 255;
void left_motor_forward(int speed = DEFAULT_SPEED) {
  analogWrite(LEFT_SPEED, speed);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACK, LOW);
}

void left_motor_back(int speed = DEFAULT_SPEED) {
  analogWrite(LEFT_SPEED, speed);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACK, HIGH);
}

void right_motor_forward(int speed = DEFAULT_SPEED) {
  analogWrite(RIGHT_SPEED, speed);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACK, LOW);
}

void right_motor_back(int speed = DEFAULT_SPEED) {
  analogWrite(RIGHT_SPEED, speed);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACK, HIGH);
}*/

void loop() {
  /*
  stop_motor();
  digitalWrite(LED_BUILTIN, LOW);
  delay(6000);
  digitalWrite(LED_BUILTIN, HIGH);
  left_motor_forward(200);
  delay(6000);
*/
}
