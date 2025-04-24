#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_GROUP_ENTRIES  \
  MOTOR_ENTRY(LEFT_FRONT, 0) \
  MOTOR_ENTRY(LEFT_BACK, 1) \
  MOTOR_ENTRY(RIGHT_FRONT, 2) \
  MOTOR_ENTRY(RIGHT_BACK, 3) \
  MOTOR_ENTRY(LEFT_ALL, 4) \
  MOTOR_ENTRY(RIGHT_ALL, 5) \
  MOTOR_ENTRY(ALL_MOTORS, 6)

struct MotorPins {
    uint8_t forward;
    uint8_t backward;
    uint8_t speed;
};

// 电机组枚举
enum class MotorGroup : int { 
  #define MOTOR_ENTRY(name, value) name = value,
    MOTOR_GROUP_ENTRIES
  #undef MOTOR_ENTRY 
};

void init_motor();
//void set_motor(const MotorPins &motor, bool forward, bool backward, int speed);
void control_motors(MotorGroup group, bool forward, bool backward, int speed);
void stop_motors(MotorGroup group = MotorGroup::ALL_MOTORS);
void forward_motors(MotorGroup group = MotorGroup::ALL_MOTORS, int speed = 255);
void backward_motors(MotorGroup group = MotorGroup::ALL_MOTORS, int speed = 255);
void test_motors();
void set_motor(const MotorPins &motor, bool forward, bool backward, int speed);
#endif