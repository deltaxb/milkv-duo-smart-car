#include "motor.h"
#include "hc_sr04.h"
#include "track_sensor.h"
#include <wiringx.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>
void stop_program() {
  wiringXGC();
  exit(0);
}

void msleep(unsigned int ms) {
  usleep(ms * 1000);
}

void adjest_GPIO() {
  system("duo-pinmux -w GP2/PWM_10");
  system("duo-pinmux -w GP3/PWM_11");
  for (int i = 6; i <= 13; ++i) {
    std::string str = "duo-pinmux -w GP" + std::to_string(i);
    str += "/GP" + std::to_string(i);
    const char *command = str.c_str();
    printf("%s\n", command);
    system(command);
  }
}

void setup() {
  adjest_GPIO();
  if(wiringXSetup("milkv_duo", nullptr) == -1) {
    printf("wiringX初始化失败\n");
    wiringXGC();
    return;
  }
  printf("start init motors\n");
  init_motor();
  printf("end init motirs\n");
  //test_motors(MAX_SPEED / 1.5);
  //forward_motors(MotorGroup::ALL_MOTORS, MAX_SPEED / 2);
  //printf("end forward\n");
  stop_motors(MotorGroup::ALL_MOTORS);
  init_hc_sr04s();
  init_track_sensors();
  printf("end setup\n");
}

const int MAX_LEVEL = 5;
void turn_left(int level) {
  forward_motors(MotorGroup::RIGHT_ALL, MAX_SPEED);
  forward_motors(MotorGroup::LEFT_ALL, MAX_SPEED / level);
}

void turn_right(int level) {
  forward_motors(MotorGroup::LEFT_ALL, MAX_SPEED);
  forward_motors(MotorGroup::RIGHT_ALL, MAX_SPEED / level);
}

namespace FOLLOW {
  //1 black
  //0 white
  int front_track_senor = 0;
  void turn(float degree) {
    const int BASE_SPEED = MAX_SPEED / 2;
    const float K = degree * BASE_SPEED;
    move_front_and_back(MotorGroup::LEFT_ALL, BASE_SPEED - K);
    move_front_and_back(MotorGroup::RIGHT_ALL, BASE_SPEED + K);
  }

  int calc_err(int state) {
    const int r = TRACK_SENSOR_PINS / 2;
    const int l = TRACK_SENSOR_PINS & 1? r : r - 1;
    int res = 0;
    for (int i = 0; i <= l; ++i) {
      //res -= (state >> i & 1) * (i + 1);
      res -= (state >> i & 1) * ((l - i) * 2 + 1);
    }
    for (int i = r; i < TRACK_SENSOR_PINS; ++i) {
      //res += (state >> i & 1) * (TRACK_SENSOR_PINS - i);
      res += (state >> i & 1) * ((i - r) * 2 + 1);
    }
    return res;
  }
  //float last_error = 0;
  float integral = 0;
  float dsum = 0;
  float last_degree = 0;
  const float K_p = 0.4;
  const float K_d = 0.2;
  const float K_i = 0;
  const int KEEP_ERRORS = 10;
  const int KEEP_DELTA_ERRORS = 3;
  int white_times = 0;
  const int ENDURE_WHITE = 1000;
  std::list<int> errs, delta_errs;
  int loop_follow() {
    int cur_state = get_track_sensor_state(front_track_senor);
    if (cur_state == 0) {
      white_times++;
      if (white_times > ENDURE_WHITE) {
        stop_motors(MotorGroup::ALL_MOTORS);
        return -1;
      }
      printf("last_degree: %.4f\n", last_degree);
      turn(last_degree);
      printf("white times: %d\n", white_times); 
      return 0;
    }
    else
      white_times = 0;
    printf("start loop follow:\n");
    printf("cur state: %d\n", cur_state);
    float error = calc_err(cur_state);
    dsum -= delta_errs.back();
    dsum += error - errs.front();
    //float delta = error - last_error;
    //if (errs.size() >= KEEP_ERRORS) {
    integral -= errs.back();
    integral += error;
    errs.pop_back();
    //}
    errs.push_front(error);
    float degree = error * K_p + (dsum / KEEP_DELTA_ERRORS) * K_d + (integral / KEEP_ERRORS) * K_i;
    printf("error: %.4f\n", error);
    printf("aver delta: %.4f\n", dsum / KEEP_DELTA_ERRORS);
    printf("integral: %.4f\n", integral / KEEP_ERRORS);
    printf("degree: %.4f\n", degree);
    turn(degree);
    last_degree = degree;
    return 0;
  }

  void follow_black_line() {
    errs.clear();
    delta_errs.clear();
    while (errs.size() < KEEP_ERRORS) {
      errs.push_front(0);
      //delta_errs.push_front(0);
    }
    while (errs.size() < KEEP_DELTA_ERRORS) {
      delta_errs.push_front(0);
    }
    integral = 0;
    dsum = 0;
    int init_state = get_track_sensor_state(front_track_senor);
    /*
    if (init_state == 0) {
      printf("no black line!\n");
      return;
    }*/
    const int MAXT = 1000 * 300;
    int t = 0;
    while (t < MAXT) {
      int result = loop_follow();
      if (result == -1) {
        printf("out of black line!\n");
        return;
      }
      const int keep_time = 10;
      msleep(keep_time);
      t += keep_time;
    }
  }
}



void loop() {
  float dis = hc_sr04_distance(0);
  float track_sensor_state = get_track_sensor_state(0);
  msleep(500);
}

int main() {
  int op;
  setup();
  scanf("%d", &op);
  printf("%d\n", op);
  
  if (op == 1) {
    stop_program();
  }
  else {
    if (op == 2) {
      while (1) {
        loop();
      }
    }
  }

  /*
  while (1) {
    loop();
  }*/
  int time = 1;
  while (time > 0) {
    FOLLOW::follow_black_line();
    sleep(2);
    time -= 2;
  }
  //test_motors();
  wiringXGC();
  return 0;
}