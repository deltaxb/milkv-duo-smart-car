#include <cstdint>
#include <cstdio>
#include <algorithm>
#include "motor.h"
#include <wiringx.h>
//#include <ctime>
#include <unistd.h> 

constexpr int VERBOSE = 0;
constexpr int PWM_PERIOD = 1e6;

const MotorPins motors[] = {
  {18, 19, 2},
  {20, 21, 3}
  /*
  {19, 20,  4},  // LEFT_FRONT
  {21, 22,  5},  // LEFT_BACK
  {24, 25, 16},  // RIGHT_FRONT
  {26, 27, 17}   // RIGHT_BACK
 */
};

// 电机组配置（每组对应的电机索引）
const uint8_t motorGroups[][3] = { // 第二维度改为5
  {0, 0xFF}, //LEFT_ALL
  {1, 0xFF}, //RIGHT_ALL
  {0, 1, 0xFF} //ALL_MOTORS
  /*
    {0, 0xFF},         // LEFT_FRONT (1个电机)
    {1, 0xFF},         // LEFT_BACK
    {2, 0xFF},         // RIGHT_FRONT
    {3, 0xFF},         // RIGHT_BACK
    {0, 1, 0xFF},      // LEFT_ALL (2个电机)
    {2, 3, 0xFF},      // RIGHT_ALL
    {0, 1, 2, 3, 0xFF} // ALL_MOTORS (4个电机)
  */
};

constexpr MotorGroup motor_groups[] = {
  #define MOTOR_ENTRY(name, value) MotorGroup::name,
  MOTOR_GROUP_ENTRIES
  #undef MOTOR_ENTRY
};

void init_motor() {
  
  for (auto& motor : motors) {
    int result = 0;
    
    result = pinMode(motor.forward, PINMODE_OUTPUT);
    if (result) {
      printf("pinMode %d\n error", motor.forward);
    }
    result = pinMode(motor.backward, PINMODE_OUTPUT);
    if (result) {
      printf("pinMode %d\n error", motor.backward);
    }
    /*
    result = pinMode(motor.speed, PINMODE_OUTPUT);
    if (result) {
      printf("pinMode %d\n error", motor.speed);
    }*/
    printf("set PWM period\n");
    if (wiringXPWMSetPeriod(motor.speed, PWM_PERIOD)) {
      printf("fail to set PWM Period\n");
    }
    printf("set PWM polarity\n");
    wiringXPWMSetPolarity(motor.speed, 0);
    printf("set PWM duty\n");
    wiringXPWMSetDuty(motor.speed, PWM_DUTY_MAX);
    printf("set init motor");
    set_motor(motor, LOW, LOW, 0);
    printf("enable PWM\n");
    wiringXPWMEnable(motor.speed, 1);
    printf("motor.forward: %d\n", motor.forward);
    printf("motor.backward: %d\n", motor.backward);
    printf("motor.speed: %d\n", motor.speed);
  }
  //stop_motors();
}

// 基础电机控制
void set_motor(const MotorPins &motor, bool forward, bool backward, int speed) {
  if (VERBOSE) {
    printf("set motors: \n");
    printf("motor.forward: %d\n", motor.forward);
    printf("motor.backward: %d\n", motor.backward);
    printf("motor.speed: %d\n", motor.speed);
  }
  digitalWrite(motor.forward, forward? HIGH : LOW);
  digitalWrite(motor.backward, backward? HIGH : LOW);
  wiringXPWMSetDuty(motor.speed, speed);
}

// 通用组控制
void control_motors(MotorGroup group, bool forward, bool backward, int speed) {
  const uint8_t* motors = motorGroups[static_cast<int>(group)];
  for(int i=0; motors[i]!=0xFF; i++) { // 以0xFF作为结束标记
    set_motor(::motors[motors[i]], forward, backward, speed);
  }
}

// 高级控制接口
void stop_motors(MotorGroup group) {
  control_motors(group, LOW, LOW, 0);
}

void forward_motors(MotorGroup group, int speed) {
  control_motors(group, HIGH, LOW, speed);
} 

void backward_motors(MotorGroup group, int speed) {
  control_motors(group, LOW, HIGH, speed);
}


//ensure initialize already
void test_motors(int speed) {
  for (MotorGroup group : motor_groups) {
    printf("start test motor %d\n", static_cast<int>(group));
    forward_motors(group, speed);
    sleep(2);
    backward_motors(group, speed);
    sleep(2);
    stop_motors(group);
    sleep(2);
    printf("end test motor %d\n", static_cast<int>(group));
  }
}

void reset() {
  for (auto motor : motors)
    wiringXPWMEnable(motor.speed, 0);
}

void move_front_and_back(MotorGroup group, int speed) {
  speed = std::min(speed, MAX_SPEED);
  speed = std::max(speed, -MAX_SPEED);
  if (speed >= 0) {
    control_motors(group, HIGH, LOW, speed);
  }
  else {
    control_motors(group, LOW, HIGH, -speed);
  }
}