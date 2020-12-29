/**
 * Arduino-controlled light dimmer for night lights
 *
 * by Stuart Sonatina
 */

#define LED_PIN 9
#define POT_PIN A0

// current time for timers
unsigned long currMillis;

// heartbeat timer
const long heartbeatTimerInterval = 1000;
unsigned long heartPrevMillis = 0;
bool heartbeatState = LOW;

int pwmOut = 0; // pwmOut for writing to LED_PIN
int pwmIn; // for reading potentiometer

void setup() {
  // Initialize pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);

  Serial.begin(9600); // serial for debug
} // setup

void loop() {
  // get current time for timers
	currMillis = millis();
  heartbeat();

  // read pot pin and analogWrite LED_PIN the brightness from that input
  pwmIn = analogRead(POT_PIN);
  Serial.println(pwmIn);
  int writeValue = map(pwmIn, 0,1023, 0,255);
  analogWrite(LED_PIN, writeValue);
  // Serial.println(writeValue);

} // loop


void heartbeat() {
  if(currMillis-heartPrevMillis > heartbeatTimerInterval)
  {
    heartbeatState = !heartbeatState;
    digitalWrite(LED_BUILTIN, heartbeatState);
    heartPrevMillis = currMillis;
  }
}
