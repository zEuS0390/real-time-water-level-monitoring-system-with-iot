// Include necessary libraries
#include <Group11Arduino.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <HardwareSerial.h>

// Define constants for configuration
#define SERIAL_COMMUNICATION_BAUD_RATE      9600
#define LIQUID_CRYSTAL_I2C_ADDRESS          0x27
#define LIQUID_CRYSTAL_NUMBER_OF_COLUMNS    16
#define LIQUID_CRYSTAL_NUMBER_OF_ROWS       2
#define WATER_LEVEL_SENSOR_PIN              A0
#define RAIN_SENSOR_PIN                     A3
#define ULTRASONIC_SENSOR_TRIGGER_PIN       5
#define ULTRASONIC_SENSOR_ECHO_PIN          6
#define RAIN_HEAVY_THRESHOLD                300
#define WATER_LEVEL_INDICATOR_LEVEL1_PIN    A0
#define WATER_LEVEL_INDICATOR_LEVEL2_PIN    A1
#define WATER_LEVEL_INDICATOR_LEVEL3_PIN    A2

// Use the Group11Arduino namespace
using namespace Group11Arduino;    

// Create instances of classes
WaterLevelSensor        waterlevel_sensor       (WATER_LEVEL_INDICATOR_LEVEL1_PIN,
                                                 WATER_LEVEL_INDICATOR_LEVEL2_PIN,
                                                 WATER_LEVEL_INDICATOR_LEVEL3_PIN);
RainSensor              rain_sensor             (RAIN_SENSOR_PIN);
UltrasonicSensor        ultrasonic_sensor       (ULTRASONIC_SENSOR_TRIGGER_PIN,
                                                 ULTRASONIC_SENSOR_ECHO_PIN);
LiquidCrystal_I2C       lcd                     (LIQUID_CRYSTAL_I2C_ADDRESS, 
                                                 LIQUID_CRYSTAL_NUMBER_OF_COLUMNS,
                                                 LIQUID_CRYSTAL_NUMBER_OF_ROWS);

// Setup function, executed once on startup
void setup() {
  Serial.begin(SERIAL_COMMUNICATION_BAUD_RATE);   // Initialize serial communication
  rain_sensor.init(INPUT);                        // Initialize rain sensor
  waterlevel_sensor.init(INPUT, INPUT, INPUT);    // Initialize water level sensor
  ultrasonic_sensor.init(OUTPUT, INPUT);          // Initialize ultrasonic sensor
  lcd.init();                                     // Initialize LCD
  lcd.backlight();                                // Turn on LCD backlight
}

// Main loop function, continuously reads sensor values and prints them
void loop() {

  // Read sensor values
  Result<RainIntensityType> rainintensity =  rain_sensor.read(RAIN_HEAVY_THRESHOLD);  // Read rain sensor
  Result<WaterLevelType>    waterlevel    =  waterlevel_sensor.read();                // Read water level sensor
  Result<DistanceType>      distance      =  ultrasonic_sensor.read();                // Read ultrasonic sensor

  // Print sensor values on LCD
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.print(rainintensity.value);
  lcd.print(" ");
  lcd.print("W:");
  lcd.print(enumToString(waterlevel.type));
  lcd.print("          ");

  lcd.setCursor(0, 1);
  lcd.print("D:");
  lcd.print(distance.value);
  lcd.print("          ");

  // Create a JSON object
  StaticJsonDocument<800> mainDoc;

  // Create a nested JSON object for sensor values
  JsonObject sensorValues = mainDoc.createNestedObject("group11");

  // Store sensor values inside the nested JSON object
  sensorValues["rain"]["value"] = rainintensity.value;                // Store rain intensity value
  sensorValues["rain"]["type"] = enumToString(rainintensity.type);    // Store rain intensity type
  sensorValues["water"]["value"] = waterlevel.value;                  // Store water level value
  sensorValues["water"]["type"] = enumToString(waterlevel.type);      // Store water level type
  sensorValues["distance"]["value"] = distance.value;                 // Store distance value
  sensorValues["distance"]["type"] = "cm";                            // Store distance type

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(mainDoc, jsonString);

  // Print the JSON string over the serial port
  Serial.println(jsonString);

  delay(1000);  // Delay for 1 second
}
