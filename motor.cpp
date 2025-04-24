#include <Arduino.h>
#include <cstdint>
#include "motor.h"

#ifdef _WIN32
#define ENDL \r\n
#else
#define ENDL \n
#endif

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

constexpr MotorGroup motor_groups[] = {
  #define MOTOR_ENTRY(name, value) MotorGroup::name,
  MOTOR_GROUP_ENTRIES
  #undef MOTOR_ENTRY
};

void init_motor() {
  for (auto& motor : motors) {
    pinMode(motor.forward, OUTPUT);
    pinMode(motor.backward, OUTPUT);
    pinMode(motor.speed, OUTPUT);
    set_motor(motor, LOW, LOW, 0);
  }
  //stop_motors();
}

// 基础电机控制
void set_motor(const MotorPins &motor, bool forward, bool backward, int speed) {
  digitalWrite(motor.forward, forward);
  digitalWrite(motor.backward, backward);
  analogWrite(motor.speed, speed);
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
void test_motors() {
  for (MotorGroup group : motor_groups) {
    Serial.printf("start test motor %d\r\n", static_cast<int>(group));
    /*
    const int label_time = (static_cast<int>(group) + 1) * 1000;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(label_time);
    digitalWrite(LED_BUILTIN, LOW);
    */
    forward_motors(group);
    delay(2000);
    backward_motors(group);
    delay(2000);
    stop_motors(group);
    delay(1000);
    Serial.printf("end test motor %d\r\n", static_cast<int>(group));
  }
}