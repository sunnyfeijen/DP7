#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 300

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int val = 0;
int prev;

void setup() {

  Serial.begin(9600);           // start serial for output
}

void loop() {

  prev = val;

  unsigned int uS = sonar.ping(); 
  val = uS / US_ROUNDTRIP_CM;

  if(prev - val > 20){
    Serial.println("closer"); 
  }
  
  delay(1000);   
}
