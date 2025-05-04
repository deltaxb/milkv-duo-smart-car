#include "track_sensor.h"
#include <wiringx.h>
#include <cstdio>

#define TRACK_SENSOR_DEBUG

const int NUM = 8;
const int sensor_pins[][NUM] = {
  {21, 22, 15, 14, 17, 29, 31, 32}
};

void init_track_sensors() {
  for (auto &id : sensor_pins)
    for (auto &pins : id)
      pinMode(pins, PINMODE_INPUT);
} 

int get_track_sensor_state(int id) {
  int state = 0;
  for (int j = 0; j < NUM; ++j) {
    int info = digitalRead(sensor_pins[id][j]);
    state = state << 1 | info;
    //Serial.println(state);
  }
  #ifdef TRACK_SENSOR_DEBUG
  printf("track sensor %d state: %d\n", id, state);
  #endif
  return state;
}