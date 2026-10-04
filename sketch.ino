#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// PIN CONFIGURATION
#define PH_SENSOR_PIN     A0
#define TEMP_SENSOR_PIN   7
#define PUMP_PIN          8
#define AERATOR_PIN       9
#define LED_GREEN_PIN     10
#define LED_RED_PIN       11
#define BUZZER_PIN        12

// OBJECTS
OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature tempSensor(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// THRESHOLDS
const float PH_MIN = 6.5;
const float PH_MAX = 8.0;
const float TEMP_MIN = 25.0;
const float TEMP_MAX = 30.0;

// VARIABLES
float phValue = 7.0;
float temperatureC = 0.0;
String condition = "NORMAL";

// FUNCTION: Read simulated pH
// Potentiometer represents the analog output of a pH sensor.
// Wokwi analog range: 0 - 1023
// Converted to simulated pH range: 0 - 14
float readPH() {
  int rawValue = analogRead(PH_SENSOR_PIN);

  float ph = (rawValue / 1023.0) * 14.0;

  return ph;
}

// FUNCTION: Determine condition
void determineCondition() {
  if (phValue < PH_MIN) {
    condition = "PH TERLALU ASAM";
  }
  else if (phValue > PH_MAX) {
    condition = "PH TERLALU BASA";
  }
  else if (temperatureC < TEMP_MIN) {
    condition = "SUHU RENDAH";
  }
  else if (temperatureC >= TEMP_MAX) {
    condition = "SUHU TINGGI";
  }
  else {
    condition = "NORMAL";
  }
}

// FUNCTION: Control actuators
void controlActuators() {

  if (condition == "NORMAL") {

    digitalWrite(PUMP_PIN, LOW);
    digitalWrite(AERATOR_PIN, LOW);

    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_RED_PIN, LOW);

    noTone(BUZZER_PIN);
  }
  else {

    digitalWrite(PUMP_PIN, HIGH);
    digitalWrite(AERATOR_PIN, HIGH);

    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, HIGH);

    tone(BUZZER_PIN, 1000);
  }
}

// FUNCTION: Update LCD
void updateLCD() {

  lcd.clear();

  // Line 1: pH and temperature
  lcd.setCursor(0, 0);
  lcd.print("pH:");
  lcd.print(phValue, 1);
  lcd.print(" T:");
  lcd.print(temperatureC, 0);
  lcd.print("C");

  // Line 2: condition
  lcd.setCursor(0, 1);
  if (condition == "NORMAL") {
    lcd.print("AIR: NORMAL");
  }
  else if (condition == "PH TERLALU ASAM") {
    lcd.print("PH: ASAM!");
  }
  else if (condition == "PH TERLALU BASA") {
    lcd.print("PH: BASA!");
  }
  else if (condition == "SUHU RENDAH") {
    lcd.print("SUHU RENDAH");
  }
  else if (condition == "SUHU TINGGI") {
    lcd.print("SUHU TINGGI");
  }
}

//Serial monitoring
void updateSerial() {
  Serial.println("SMART POND MONITORING");
  Serial.print("pH Air      : ");
  Serial.println(phValue, 2);
  Serial.print("Suhu Air    : ");
  Serial.print(temperatureC, 2);
  Serial.println(" C");
  Serial.print("Kondisi     : ");
  Serial.println(condition);
  Serial.println();
  Serial.print("Pompa       : ");
  Serial.println(condition == "NORMAL" ? "OFF" : "ON");
  Serial.print("Aerator     : ");
  Serial.println(condition == "NORMAL" ? "OFF" : "ON");
  Serial.println();
}

// SETUP
void setup() {
  Serial.begin(9600);
  pinMode(PH_SENSOR_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(AERATOR_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initial actuator state
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(AERATOR_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);

  noTone(BUZZER_PIN);

  // Start DS18B20
  tempSensor.begin();

  // Start LCD
  lcd.init();
  lcd.backlight();

  // STARTUP DISPLAY
  Serial.println();
  Serial.println("Nama : Erlangga Aghna Fatah");
  Serial.println("NIM  : 24051204040");
  Serial.println();
  Serial.println("SYSTEM INITIALIZING...");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Erlangga Aghna F");
  lcd.setCursor(0, 1);
  lcd.print("24051204040");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready!");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring...");
  delay(1500);

  Serial.println("System Ready!");
  Serial.println();
}

// LOOP
void loop() {

  // Read pH simulator
  phValue = readPH();

  // Read DS18B20
  tempSensor.requestTemperatures();
  temperatureC = tempSensor.getTempCByIndex(0);

  // Check sensor error
  if (temperatureC == DEVICE_DISCONNECTED_C) {
    Serial.println("ERROR: DS18B20 tidak terdeteksi!");
    temperatureC = 0.0;
  }

  determineCondition();
  controlActuators();
  updateLCD();
  updateSerial();
  delay(1000);
}
