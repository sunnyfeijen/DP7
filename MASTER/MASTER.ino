#include <Wire.h>
#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 350

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int x = 0;
int val = 0;
int prev;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  x = 0;
  prev = val;

  unsigned int uS = sonar.ping();
  val = uS / US_ROUNDTRIP_CM;
  Serial.println(val);
  if(prev - val > 30){
    x = 1;
    Serial.println("closer");
    Wire.beginTransmission(8);
    Wire.write(x);
    Wire.endTransmission();
    delay(5000);
  }
  
  delay(50);
}
