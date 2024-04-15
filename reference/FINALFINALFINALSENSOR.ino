#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);
#define TRIGGER_PIN 2
#define ECHO_PIN 3

LiquidCrystal_I2C lcd(0x27, 16, 2);
  
unsigned long startTime;
unsigned long elapsedTime;
float minDistance = 0.01;
float maxDistance = 7;
float distanceSum = 0.0;
int numReadings = 0;
float thresholdDistance = 4.0;
float distance_m;

String phoneNumber = "+639190037493";

bool sentless3mSMS = false;
bool sent3mSMS = false;
bool sent4mSMS = false;
bool sent5mSMS = false;

unsigned long lastSMSTime = 0;
unsigned long smsInterval = 60000; // 1 minute interval

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Setting SIM800L EVB to receive mode...");
  mySerial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);

  while (mySerial.available()) {
    char c = mySerial.read();
    Serial.print(c);
  }

  delay(1000);

  Serial.println("Sending AT+CMGF=1 command...");
  mySerial.print("AT+CMGF=1\r");
  delay(100);

  while (mySerial.available()) {
    char c = mySerial.read();
    Serial.print(c);
  }

  delay(1000);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
}

void loop() {
  long duration, distance_cm;
  float distance_m;

  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(30);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance_cm = duration * 0.0343 / 2;

  distance_m = 5 - (distance_cm / 100.0 * 1.04);

  if (distance_m >= maxDistance) {
    distance_m = maxDistance;
  }

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");

  if (distance_m < 1.0) {
    lcd.setCursor(0, 0);
    lcd.print("                        ");
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("Dis < 1m");
  } else {
    lcd.print(distance_m, 2);
    lcd.print(" m");
  }

  elapsedTime = millis() - startTime;

  if (elapsedTime >= 10000) {
    float averageDistance = distanceSum / numReadings;

    if (averageDistance >= maxDistance) {
      averageDistance = maxDistance;
    }

    lcd.setCursor(0, 1);
    lcd.print("Avg: ");
    lcd.print(averageDistance, 2);
    lcd.print(" m ");

    distanceSum = 0.0;
    numReadings = 0;
    startTime = millis();

    delay(3000);
  } else {
    distanceSum += distance_m;
    numReadings++;
  }

  delay(500);

    if (distance_m > 4.0 && !sent4mSMS) {
    Serial.println("Sending SMS notification for 4 meters...");
    mySerial.print("AT+CMGF=1\r");
    delay(1000);
    mySerial.print("AT+CMGS=\"" + phoneNumber + "\"\r");
    delay(1000);
    mySerial.print("RIVER WATER LEVEL GREATER THAN 4m: Students and Teachers must evacuate immediately to avoid further dangers.");
    delay(1000);
    mySerial.write((char)26);
    delay(1000);
    Serial.println("Sent SMS notification for 4 meters");
    sent4mSMS = true;
  } else if (distance_m > 3.0 && !sent3mSMS) {
    Serial.println("Sending SMS notification for 3 meters...");
    mySerial.print("AT+CMGF=1\r");
    delay(1000);
    mySerial.print("AT+CMGS=\"" + phoneNumber + "\"\r");
    delay(1000);
    mySerial.print("RIVER WATER LEVEL GREATER THAN 3m: Students and Teachers must be ready for impending dangers in San Jose del Monte National High School due to flood susceptibility.");
    delay(1000);
    mySerial.write((char)26);
    delay(1000);
    Serial.println("Sent SMS notification for 3 meters");
    sent3mSMS = true;
  } else if (distance_m < 3.0 && !sentless3mSMS) {
    Serial.println("Sending SMS notification for less 3 meters...");
    mySerial.print("AT+CMGF=1\r");
    delay(1000);
    mySerial.print("AT+CMGS=\"" + phoneNumber + "\"\r");
    delay(1000);
    mySerial.print("RIVER WATER LEVEL LESS THAN 3m: Students and Teachers can rest assured that San Jose del Monte National High School is safe from flooding.");
    delay(1000);
    mySerial.write((char)26);
    delay(1000);
    Serial.println("Sent SMS notification for 3 meters");
    sentless3mSMS = true;
  }

  // Send SMS every minute
  if (millis() - lastSMSTime >= smsInterval) {
    Serial.println("Sending SMS notification for current distance...");
    mySerial.print("AT+CMGF=1\r");
    delay(1000);
    mySerial.print("AT+CMGS=\"" + phoneNumber + "\"\r");
    delay(1000);
    mySerial.print("Current Water Level: " + String(distance_m) + " meters.");
    delay(1000);
    mySerial.write((char)26);
    delay(1000);
    Serial.println("Sent SMS notification for current distance");
    lastSMSTime = millis();
  }
}
