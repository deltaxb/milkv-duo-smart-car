#include "hc_sr04.h"
#include <Arduino.h>

#define HC_SR04_DEBUG

//#define MAX_NUM 10
const int trig_pins[] = {19};
const int echo_pins[] = {20};

void init_hc_sr04s() {
  for (auto &trig_pin : trig_pins) {
    pinMode(trig_pin, OUTPUT);
  }
  for (auto &echo_pin : echo_pins) {
    pinMode(echo_pin, INPUT);
  }
}

float hc_sr04_distance(int id) {
  const int trig_pin = trig_pins[id];
  const int echo_pin = echo_pins[id];
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  Serial.println("start calculate");
  float duration = pulseIn(echo_pin, HIGH);
  Serial.println("end calculate");
  float distance = (duration * .0343)/2;
  #ifdef HC_SR04_DEBUG
  Serial.print("Distance: ");
  Serial.println(distance);
  #endif
  //delay(100);
  return distance;
}