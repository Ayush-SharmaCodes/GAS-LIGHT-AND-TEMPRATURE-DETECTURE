// ========================================
// FIRE AND GAS DETECTION SYSTEM
// Tinkercad - Arduino UNO
// ========================================

const int gasPin = A0;
const int tempPin = A1;
const int ldrPin = A2;

const int buzzerPin = 8;
const int ledPin = 9;

// Threshold values
const int gasThreshold = 720;
const int lightThreshold = 700;
const float temperatureThreshold = 40.0;


void setup() {

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
}


void loop() {

  // ==============================
  // GAS SENSOR
  // ==============================

  int gasValue = analogRead(gasPin);


  // ==============================
  // LDR
  // ==============================

  int lightValue = analogRead(ldrPin);


  // ==============================
  // TMP36
  // ==============================

  int tempReading = analogRead(tempPin);

  float voltage = tempReading * (5.0 / 1023.0);

  float temperature = (voltage - 0.5) * 100.0;


  // ==============================
  // SERIAL MONITOR
  // ==============================

  Serial.print("Gas: ");
  Serial.print(gasValue);

  Serial.print(" | Temperature: ");
  Serial.print(temperature);
  Serial.print(" C");

  Serial.print(" | Light: ");
  Serial.println(lightValue);


  // ==============================
  // DETECTION
  // ==============================

  bool gasDetected = gasValue > gasThreshold;

  bool temperatureDetected =
    temperature > temperatureThreshold;

  bool fireLightDetected =
    lightValue > lightThreshold;


  // ==============================
  // DANGER LEVEL
  // ==============================

  int dangerLevel = 0;

  if (gasDetected) {
    dangerLevel++;
  }

  if (temperatureDetected) {
    dangerLevel++;
  }

  if (fireLightDetected) {
    dangerLevel++;
  }


  // ==============================
  // ALARM
  // ==============================

  if (dangerLevel > 0) {

    // Buzzer ON
    digitalWrite(buzzerPin, HIGH);


    // ONE CONDITION
    // Slow blinking
    if (dangerLevel == 1) {

      digitalWrite(ledPin, HIGH);
      delay(500);

      digitalWrite(ledPin, LOW);
      delay(500);
    }


    // TWO CONDITIONS
    // Medium blinking
    else if (dangerLevel == 2) {

      digitalWrite(ledPin, HIGH);
      delay(250);

      digitalWrite(ledPin, LOW);
      delay(250);
    }


    // THREE CONDITIONS
    // Fast blinking
    else {

      digitalWrite(ledPin, HIGH);
      delay(100);

      digitalWrite(ledPin, LOW);
      delay(100);
    }

  }


  // ==============================
  // SAFE CONDITION
  // ==============================

  else {

    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);

    delay(100);
  }
}