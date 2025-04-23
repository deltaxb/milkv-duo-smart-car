#include <Arduino.h>
#include <cstdint>
#include "motor.h"

const MotorPins motors[] = {
    {19, 20,  4},  // LEFT_FRONT
    {21, 22,  5},  // LEFT_BACK
    {24, 25, 16},  // RIGHT_FRONT
    {26, 27, 17}   // RIGHT_BACK
};

// 电机组配置（每组对应的电机索引）
const uint8_t motorGroups[7][5] = { // 第二维度改为5
    {0, 0xFF},         // LEFT_FRONT (1个电机)
    {1, 0xFF},         // LEFT_BACK
    {2, 0xFF},         // RIGHT_FRONT
    {3, 0xFF},         // RIGHT_BACK
    {0, 1, 0xFF},      // LEFT_ALL (2个电机)
    {2, 3, 0xFF},      // RIGHT_ALL
    {0, 1, 2, 3, 0xFF} // ALL_MOTORS (4个电机)
};

void init_motor() {
  for (auto& motor : motors) {
    pinMode(motor.forward, OUTPUT);
    pinMode(motor.backward, OUTPUT);
    pinMode(motor.speed, OUTPUT);
  }
}

// 基础电机控制
void set_motor(const MotorPins &motor, bool forward, bool backward, int speed) {
  digitalWrite(motor.forward, forward);
  digitalWrite(motor.backward, backward);
  analogWrite(motor.speed, speed);
}

// 通用组控制
void control_motors(MotorGroup group, bool forward, bool backward, int speed) {
  const uint8_t* motors = motorGroups[group];
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