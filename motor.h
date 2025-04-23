#ifndef MOTOR_H
#define MOTIR_H

struct MotorPins {
    uint8_t forward;
    uint8_t backward;
    uint8_t speed;
};

// 电机组枚举
enum MotorGroup {
  LEFT_FRONT  = 0,
  LEFT_BACK   = 1,
  RIGHT_FRONT = 2,
  RIGHT_BACK  = 3,
  LEFT_ALL    = 4,
  RIGHT_ALL   = 5,
  ALL_MOTORS  = 6
};

void init_motor();
//void set_motor(const MotorPins &motor, bool forward, bool backward, int speed);
void control_motors(MotorGroup group, bool forward, bool backward, int speed);
void stop_motors(MotorGroup group = ALL_MOTORS);
void forward_motors(MotorGroup group = ALL_MOTORS, int speed = 255);
void backward_motors(MotorGroup group = ALL_MOTORS, int speed = 255);
#endif