#include "motor.h"
#include "hc_sr04.h"
#include "track_sensor.h"
#include <wiringx.h>
#include <unistd.h>
#include <cstdio>
void setup() {
  if(wiringXSetup("milkv_duo", NULL) == -1) {
    printf("wiringX初始化失败\n");
    wiringXGC();
    return;
  }
  printf("start init motors\n");
  init_motor();
  printf("end init motirs\n");
  forward_motors(MotorGroup::ALL_MOTORS, 30);
  printf("end forward\n");
  delayMicroseconds(1000);
  stop_motors(MotorGroup::ALL_MOTORS);
  delayMicroseconds(1000);
  init_hc_sr04s();
  init_track_sensors();
  usleep(2e6);
}

namespace FOLLOW {
  int front_track_senor = 0;
  void loop_follow() {
    int cur_state = get_track_sensor_state(front_track_senor);
  }

  void follow_black_line() {
    int init_state = get_track_sensor_state(front_track_senor);
    if (init_state == 0) {
      return;
    }
  }
}


void loop() {
  float dis = hc_sr04_distance(0);
  float track_sensor_state = get_track_sensor_state(0);
  delayMicroseconds(500);
}

int main() {
  setup();
  while (1) {
    loop();
  }
  return 0;
}