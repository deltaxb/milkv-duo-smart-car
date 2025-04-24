#include "motor.h"
#include "hc_sr04.h"

void light_LED(int time) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  Serial.begin(115200);
  Serial.println("start setup");
  pinMode(LED_BUILTIN, OUTPUT);
  light_LED(2000);
  
  init_motor();
  test_motors();

  init_hc_sr04s();
  hc_sr04_distance(0);
  // Serial.print("")
  // Serial.println();

  Serial.println("finish setup");
  Serial.flush();
}

void loop() {

  // Serial.println("fuck");
  // Serial.flush();
}
