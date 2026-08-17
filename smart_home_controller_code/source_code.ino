#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ================= PIN DEFINITIONS =================

// Sensors
#define PIR_PIN 13
#define LDR_PIN 34
#define DHT_PIN 14

// Relays
#define LIGHT_RELAY 26
#define FAN_RELAY 25

// LEDs
#define YELLOW_LED 18
#define BLUE_LED 19
#define RED_LED 16
#define GREEN_LED 17

// Buzzer
#define BUZZER_PIN 27

// Buttons
#define SECURITY_BUTTON 33
#define LIGHT_BUTTON 32
#define FAN_BUTTON 23

// DHT
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

// LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= VARIABLES =================

bool securityMode = false;
bool manualLight = false;
bool manualFan = false;

bool lightState = false;
bool fanState = false;
bool alarmState = false;

bool lastSecurityButton = HIGH;
bool lastLightButton = HIGH;
bool lastFanButton = HIGH;

unsigned long lastMotionTime = 0;

const int DARK_THRESHOLD = 2000;
const float FAN_ON_TEMP = 30.0;
const float FAN_OFF_TEMP = 28.0;

const unsigned long LIGHT_TIMEOUT = 5000;

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  // Sensors
  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  // Outputs
  pinMode(LIGHT_RELAY, OUTPUT);
  pinMode(FAN_RELAY, OUTPUT);

  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  // Buttons
  pinMode(SECURITY_BUTTON, INPUT_PULLUP);
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);
  pinMode(FAN_BUTTON, INPUT_PULLUP);

  // Start outputs OFF
  digitalWrite(LIGHT_RELAY, LOW);
  digitalWrite(FAN_RELAY, LOW);

  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  digitalWrite(BUZZER_PIN, LOW);

  // DHT
  dht.begin();

  // LCD
  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Smart Home");
  lcd.setCursor(0, 1);
  lcd.print("Controller Ready");

  delay(2000);

  lcd.clear();

  Serial.println("================================");
  Serial.println("   SMART HOME CONTROLLER");
  Serial.println("================================");
}

// ================= BUTTON HANDLING =================

void readButtons() {

  bool securityReading = digitalRead(SECURITY_BUTTON);
  bool lightReading = digitalRead(LIGHT_BUTTON);
  bool fanReading = digitalRead(FAN_BUTTON);

  // Security button
  if (lastSecurityButton == HIGH && securityReading == LOW) {

    securityMode = !securityMode;

    Serial.print("Security Mode: ");

    if (securityMode) {
      Serial.println("ON");
    } else {
      Serial.println("OFF");

      alarmState = false;
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(RED_LED, LOW);
    }

    delay(200);
  }

  // Manual light button
  if (lastLightButton == HIGH && lightReading == LOW) {

    manualLight = !manualLight;

    Serial.print("Manual Light: ");

    if (manualLight) {
      Serial.println("ON");
    } else {
      Serial.println("OFF");
    }

    delay(200);
  }

  // Manual fan button
  if (lastFanButton == HIGH && fanReading == LOW) {

    manualFan = !manualFan;

    Serial.print("Manual Fan: ");

    if (manualFan) {
      Serial.println("ON");
    } else {
      Serial.println("OFF");
    }

    delay(200);
  }

  lastSecurityButton = securityReading;
  lastLightButton = lightReading;
  lastFanButton = fanReading;
}

// ================= SENSOR READING =================

float readTemperature() {

  float temperature = dht.readTemperature();

  if (isnan(temperature)) {

    Serial.println("DHT22 ERROR!");

    return -100;
  }

  return temperature;
}

// ================= LIGHT CONTROL =================

void controlLight(bool motion, int ldrValue) {

  bool darkRoom = ldrValue < DARK_THRESHOLD;

  // Manual mode has priority
  if (manualLight) {

    lightState = true;
  }

  // Automatic mode
  else {

    if (motion && darkRoom) {

      lightState = true;

      lastMotionTime = millis();
    }

    // Turn OFF after timeout
    if (!motion && lightState) {

      if (millis() - lastMotionTime > LIGHT_TIMEOUT) {

        lightState = false;
      }
    }

    // Bright room = light OFF
    if (!darkRoom && !motion) {

      lightState = false;
    }
  }

  digitalWrite(LIGHT_RELAY, lightState ? HIGH : LOW);
  digitalWrite(YELLOW_LED, lightState ? HIGH : LOW);
}

// ================= FAN CONTROL =================

void controlFan(float temperature) {

  if (manualFan) {

    fanState = true;
  }

  else {

    if (temperature >= FAN_ON_TEMP) {

      fanState = true;
    }

    else if (temperature <= FAN_OFF_TEMP) {

      fanState = false;
    }
  }

  digitalWrite(FAN_RELAY, fanState ? HIGH : LOW);
  digitalWrite(BLUE_LED, fanState ? HIGH : LOW);
}

// ================= SECURITY SYSTEM =================

void securitySystem(bool motion) {

  if (securityMode && motion) {

    alarmState = true;

    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RED_LED, HIGH);
  }

  else {

    alarmState = false;

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RED_LED, LOW);
  }
}

// ================= LCD DISPLAY =================

void updateLCD(float temperature, bool motion, int ldrValue) {

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("T:");

  if (temperature > -50) {
    lcd.print(temperature, 1);
  } else {
    lcd.print("ERR");
  }

  lcd.print(" L:");

  if (lightState) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }

  lcd.print(" F:");

  if (fanState) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }

  lcd.setCursor(0, 1);

  if (alarmState) {

    lcd.print("INTRUDER ALERT");
  }

  else if (securityMode) {

    lcd.print("SEC:ON ");

    if (motion) {
      lcd.print("MOTION");
    } else {
      lcd.print("SAFE");
    }
  }

  else {

    lcd.print("SEC:OFF ");

    if (motion) {
      lcd.print("MOTION");
    } else {
      lcd.print("SAFE");
    }
  }
}

// ================= SERIAL MONITOR =================

void printStatus(float temperature, int ldrValue, bool motion) {

  Serial.println();
  Serial.println("--------------------------------");

  Serial.print("Temperature: ");

  if (temperature > -50) {
    Serial.print(temperature);
    Serial.println(" C");
  }

  else {
    Serial.println("ERROR");
  }

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  Serial.print("Room: ");

  if (ldrValue < DARK_THRESHOLD) {
    Serial.println("DARK");
  }

  else {
    Serial.println("BRIGHT");
  }

  Serial.print("Motion: ");

  if (motion) {
    Serial.println("DETECTED");
  }

  else {
    Serial.println("NO MOTION");
  }

  Serial.print("Light: ");

  if (lightState) {
    Serial.println("ON");
  }

  else {
    Serial.println("OFF");
  }

  Serial.print("Fan: ");

  if (fanState) {
    Serial.println("ON");
  }

  else {
    Serial.println("OFF");
  }

  Serial.print("Security: ");

  if (securityMode) {
    Serial.println("ON");
  }

  else {
    Serial.println("OFF");
  }

  Serial.print("Alarm: ");

  if (alarmState) {
    Serial.println("ACTIVE");
  }

  else {
    Serial.println("SAFE");
  }

  Serial.println("--------------------------------");
}

// ================= MAIN LOOP =================

void loop() {

  // Read buttons
  readButtons();

  // Read sensors
  bool motion = digitalRead(PIR_PIN);

  int ldrValue = analogRead(LDR_PIN);

  float temperature = readTemperature();

  // Automatic systems
  controlLight(motion, ldrValue);

  if (temperature > -50) {
    controlFan(temperature);
  }

  // Security
  securitySystem(motion);

  // Green LED = system running
  digitalWrite(GREEN_LED, HIGH);

  // Display
  updateLCD(temperature, motion, ldrValue);

  // Serial monitor
  printStatus(temperature, ldrValue, motion);

  delay(500);
}
