#include "track_sensor.h"
#include <wiringx.h>
#include <cstdio>
#include <iostream>
#include <bitset>

#define TRACK_SENSOR_DEBUG

const int FULL_STATE = (1 << TRACK_SENSOR_PINS) - 1;
const int sensor_pins[][TRACK_SENSOR_PINS] = {
  {7, 9, 10, 16}
  //{7, 8, 9, 10, 11, 16}
  //{6, 7, 8, 9, 10, 11, 16, 17}
  //{21, 22, 15, 14, 17, 29, 31, 32}
};

void init_track_sensors() {
  for (auto &id : sensor_pins)
    for (auto &pins : id)
      pinMode(pins, PINMODE_INPUT);
} 

int get_track_sensor_state(int id) {
  int state = 0;
  for (int j = 0; j < TRACK_SENSOR_PINS; ++j) {
    int info = digitalRead(sensor_pins[id][j]);
    state = state << 1 | info;
    //Serial.println(state);
  }
  state = FULL_STATE ^ state;
  #ifdef TRACK_SENSOR_DEBUG
  std::cout << "track sensor " << id << " state: " << std::bitset<8>(state) << std::endl;
  printf("track sensor %d state: %d\n", id, state);
  #endif
  return state;
}