#include <Wire.h>
#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 100

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int x;
long timeBypasser = 0;
long timeFirstSignal = 0;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  if (x == 1 && timeFirstSignal == 0){
    timeFirstSignal = millis();

    while(timeBypasser == 0){
      unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
      int sensorDistance = (uS / US_ROUNDTRIP_CM);
      if (sensorDistance > 0){
        Serial.println(sensorDistance);
        timeBypasser = millis();
        int duration = (timeBypasser - timeFirstSignal);
        Serial.print("Time Bypasser: ");
        Serial.println(timeBypasser);
        Serial.print("Time First Signal: ");
        Serial.println(timeFirstSignal);
        Serial.print("Duration: ");
        Serial.println(duration);
      }
    }
    x = 0;
    timeFirstSignal = 0;
    timeBypasser = 0;
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  x = Wire.read();    // receive byte as an integer
  Serial.println("RECEIVED SIGNAL");
}
