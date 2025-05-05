#include "hc_sr04.h"
#include <wiringx.h>
#include <cstdio>
#include <chrono>
#include <unistd.h>

#define HC_SR04_DEBUG

//#define MAX_NUM 10
const int trig_pins[] = {15};
const int echo_pins[] = {14};

void init_hc_sr04s() {
  for (auto &trig_pin : trig_pins) {
    pinMode(trig_pin, PINMODE_OUTPUT);
  }
  for (auto &echo_pin : echo_pins) {
    pinMode(echo_pin, PINMODE_INPUT);
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
  while (digitalRead(echo_pin) == LOW) {
    usleep(1);
  }

  auto start_time = std::chrono::high_resolution_clock::now();
  while (digitalRead(echo_pin) == HIGH) {
    usleep(1);
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  //float test_duration = (end_time - start_time).count();
  float duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  //printf("%.4f %.4f\n", test_duration, duration);
  float distance = (duration * .0343)/2;
  #ifdef HC_SR04_DEBUG
  printf("Distance: %.4f\n", distance);
  #endif
  //delay(100);
  return distance;
}