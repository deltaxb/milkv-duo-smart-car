#include "motor.h"
#include "hc_sr04.h"
#include "track_sensor.h"
#include <Wire.h>

void light_LED(int time) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time);
  //digitalWrite(LED_BUILTIN, LOW);
}

void extinguish_LED(int time) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
  //digitalWrite(LED_BUILTIN, HIGH);
}

void scanI2C() {
  Serial.println("Scanning I2C devices...");
  for (int addr = 1; addr < 128; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Device found at 0x");
      Serial.println(addr, HEX);
    }
  }
}

void receive(int a) {
  Serial.printf("receive %d bytes\n\r", a);
  while(a--) {
    Serial.printf("%d \n\r", Wire1.read());
  }
}

byte val = 0;       

void setup() {
  Serial.begin(115200);
  /**
  Wire1.begin();
  Wire1.onReceive(receive);
  Wire.begin();
  Wire.print();
  Serial.printf("test slave\n\r");
  wire1.print();*/
  Serial.println("start setup");
  pinMode(LED_BUILTIN, OUTPUT);
  light_LED(2000);
  
  init_motor();
  forward_motors(MotorGroup::ALL_MOTORS, 30);
  delay(2000);
  stop_motors(MotorGroup::ALL_MOTORS);
  //test_motors(200);
  //scanI2C();
  init_hc_sr04s();
  init_track_sensors();
/*
  Wire.beginTransmission(0x50);         // Transmit to device number 0x50
  Serial.printf("send %d \n\r", ++val);
  Wire.write(val);                      // Sends value byte
  Wire.endTransmission();               // Stop transmitting
  //Wire1.onService();
  delay(1000);*/
  /*
  init_hc_sr04s();
  hc_sr04_distance(0);

  init_track_sensors();
  get_track_sensor_state(0);
*/
  Serial.println("finish setup");
  Serial.flush();
}

namespace FOLLOW {
  int front_track_senor = 0;
  void loop_follow() {
    int cur_state = get_track_sensor_state(front_track_senor);
  }

  void follow_black_line() {
    int init_state = get_track_sensor_state(front_track_senor);
    if (init_state == 0) {
      Serial.println("no black line");
      return;
    }
  }
}


void loop() {
  Serial.println("start loop"); 
  //light_LED(2000);
  //extinguish_LED(2000);
  //Serial.println("end light change");
  float dis = hc_sr04_distance(0);
  float track_sensor_state = get_track_sensor_state(0);
  //Serial.println("end distance compute");
  //Serial.println(dis);
  delay(500);
/*
  Wire.beginTransmission(0x50);         // Transmit to device number 0x50
  Serial.printf("send %d \n\r", ++val);
  Wire.write(val);                      // Sends value byte
  Wire.endTransmission();               // Stop transmitting'
  */
  //Wire1.onService();
  // Serial.println("fuck");
  // Serial.flush();
}
