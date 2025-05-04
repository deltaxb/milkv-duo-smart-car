//注意到最多不能超过10个超声波模块

#ifndef HC_SR04_H
#define HC_SR04_H
/*
struct hc_sr04 {
  int trig_pin;
  int echo_pin;
};*/

void init_hc_sr04s();
float hc_sr04_distance(int id);
#endif