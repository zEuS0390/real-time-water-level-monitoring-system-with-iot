#include "constants.h"
#include "sensor_enums.h"
#include "sensor_structs.h"
#include "RainSensor.h"
#include "WaterLevelSensor.h"
#include "UltrasonicSensor.h"
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

// Create instances of classes
WaterLevelSensor        waterlevel_sensor     (WATER_LEVEL_SENSOR_PIN);
RainSensor              rain_sensor           (RAIN_SENSOR_PIN);
UltrasonicSensor        ultrasonic_sensor     (ULTRASONIC_SENSOR_TRIGGER_PIN, 
                                               ULTRASONIC_SENSOR_ECHO_PIN);
LiquidCrystal_I2C       lcd                   (0x27, 16, 2);                                               

// Setup function, executed once on startup
void setup() {
  Serial.begin(SERIAL_COMMUNICATION_BAUD_RATE); // Initialize serial communication
  rain_sensor.init(INPUT);
  waterlevel_sensor.init(INPUT);
  ultrasonic_sensor.init(OUTPUT, INPUT);
  lcd.init();
  lcd.backlight();
}

// Main loop function, continuously reads sensor values and prints them
void loop() {

  Result  <RainIntensityType> rainintensity =  rain_sensor.read();
  Result  <WaterLevelType>    waterlevel    =  waterlevel_sensor.read();
  Result  <DistanceType>      distance      =  ultrasonic_sensor.read();

  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.print(rainintensity.value);
  lcd.print(" ");
  lcd.print("W:");
  lcd.print(waterlevel.value);
  lcd.print("          ");

  lcd.setCursor(0, 1);
  lcd.print("D:");
  lcd.print(distance.value);
  lcd.print("          ");

  // Create a JSON object
  StaticJsonDocument<800> doc;
  doc["group11/rain"] = rainintensity.value;
  doc["group11/water"] = waterlevel.value;
  doc["group11/distance"] = distance.value;

  if (Serial.available() > 0) {
    String jsonStr = Serial.readStringUntil('\n');
    StaticJsonDocument<800> configDoc;
    DeserializationError error = deserializeJson(configDoc, jsonStr);
    if (!error) {
      for (JsonPair keyValue: configDoc.as<JsonObject>()) {
        doc[keyValue.key()] = keyValue.value();
      }
    }
  }

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(doc, jsonString);

  // Print the JSON string over the serial port
  Serial.println(jsonString);

  delay(1000);
}
