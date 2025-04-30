#include <Arduino.h>
#include "track_sensor.h"

#define TRACK_SENSOR_DEBUG

const int NUM = 2;
const int sensor_pins[][NUM] = {
  {21, 22}
};

void init_track_sensors() {
  for (auto &id : sensor_pins)
    for (auto &pins : id)
      pinMode(pins, INPUT);
}

int get_track_sensor_state(int id) {
  int state = 0;
  Serial.println("start get state");
  for (int j = 0; j < NUM; ++j) {
    state = state << 1 | digitalRead(sensor_pins[id][j]);
  }
  Serial.println("end get state");
  #ifdef TRACK_SENSOR_DEBUG
  Serial.printf("track sensor %d state: %d\r\n", state);
  #endif
  return state;
}