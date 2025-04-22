// #define FORWARD1 4
// #define BACK1 5
// #define FORWARD2 6
// #define BACK2 7
// #define FORWARD3 9
// #define BACK3 10
// #define FORWARD4 11
// #define BACK4 12
#define LEFT_FORWARD 4
#define LEFT_BACK 5
#define RIGHT_FORWARD 6
#define RIGHT_BACK 7

void setup() {
    /*
  pinMode(FORWARD1, OUTPUT);
  pinMode(back1, OUTPUT);
  
  pinMode(FORWARD2, OUTPUT);
  pinMode(back2, OUTPUT);

  pinMode(FORWARD3, OUTPUT);
  pinMode(back3, OUTPUT);

  pinMode(FORWARD4, OUTPUT);
  pinMode(back4, OUTPUT);
  // put your setup code here, to run once:
*/
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACK, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACK, OUTPUT)

}

void loop() {
  //Serial.printf("hello world\r\n");
  //delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  analogWrite(FORWARD1, 200);
  delay(1000);
  analogWrite(FORWARD2, 200);
  delay(1000);
  analogWrite(FORWARD3, 200);
  printf("123\n");
  // put your main code here, to run repeatedly:

}
