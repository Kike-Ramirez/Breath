int sensorPin = A1; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor

int led = 9;
int brightness = 0;    // how bright the LED is
int fadeAmount = 3;    // how many points to fade the LED by

int gstate = 0;

// KIKE: Variables to handle timing for sensor
float timerSensor = 0;
float timeSensor = 600;

// KIKE: Variables to handle timing for LED
float timerLed = 0;
float timeLed = 500

void setup() {

  Serial.begin(9600); //sets serial port for communication
  pinMode(led, OUTPUT);

  // KIKE: Store actual time in every timer
  timerSensor = millis();
  timerLed = millis();
}

void loop() {

  switch (gstate) {

    case 0:
      // KIKE: If enough time has passed (more than timeSensor - 600ms- )
      if (millis() - timerSensor >= timeSensor) {
        // Get a new time reference in timerSensor (a new timer count is started)
        timerSensor = millis();
        sensorValue = analogRead(sensorPin); // read the value from the sensor
        Serial.println(sensorValue); //prints the values coming from the sensor on the screen
        if (sensorValue > 200) {
          gstate = 1;
        }
      }
      break;
    case 1:
      brightness = brightness + fadeAmount;
      
      if ( brightness >= 255) {
        timerLed = millis();
        fadeAmount = -fadeAmount;
      }
      if (brightness < 0) {
        resetSystem();
      }

      if (millis() - timerLed >= timeLed) {
        timerLed = millis();
        analogWrite(led, brightness);
        Serial.println(brightness);
        delay(30);
        break;      
      }

  }
}

// KIKE: Not a good idea to call this function "reset". It is a reserved word in processing and you may have collateral effects... Best rename it!
void resetSystem(){
  fadeAmount = 3;
  gstate = 0;
  brightness =0;
}
