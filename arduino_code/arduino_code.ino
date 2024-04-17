#include "constants.h"
#include "sensor_enums.h"
#include "sensor_structs.h"
#include "RainSensor.h"
#include "WaterLevelSensor.h"
#include "UltrasonicSensor.h"
#include <ArduinoJson.h>

// Create instances of classes
WaterLevelSensor        waterlevel_sensor     (WATER_LEVEL_SENSOR_PIN);
RainSensor              rain_sensor           (RAIN_SENSOR_PIN);
UltrasonicSensor        ultrasonic_sensor     (ULTRASONIC_SENSOR_TRIGGER_PIN, 
                                               ULTRASONIC_SENSOR_ECHO_PIN);

// Setup function, executed once on startup
void setup() {
  Serial.begin(SERIAL_COMMUNICATION_BAUD_RATE); // Initialize serial communication
  rain_sensor.init(INPUT);
  waterlevel_sensor.init(INPUT);
  ultrasonic_sensor.init(OUTPUT, INPUT);
}

// Main loop function, continuously reads sensor values and prints them
void loop() {

  Result  <RainIntensityType> rainintensity =  rain_sensor.read();
  Result  <WaterLevelType>    waterlevel    =  waterlevel_sensor.read();
  Result  <DistanceType>      distance      =  ultrasonic_sensor.read();

  // Create a JSON object
  StaticJsonDocument<200> doc;
  doc["group11/rain"] = rainintensity.value;
  doc["group11/water"] = waterlevel.value;
  doc["group11/distance"] = distance.value;

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(doc, jsonString);

  // Print the JSON string over the serial port
  Serial.println(jsonString);

  delay(1000);
}
