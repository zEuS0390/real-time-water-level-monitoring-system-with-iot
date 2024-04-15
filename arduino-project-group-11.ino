#include "constants.h"
#include "sensor_enums.h"
#include "sensor_structs.h"
#include "RainSensor.h"
#include "WaterLevelSensor.h"
#include "SMSModule.h"

// Create instances of sensor classes
SMSModule           sms_module          (SMS_MODULE_RX_PIN,
                                         SMS_MODULE_TX_PIN,
                                         SMS_MODULE_PHONE_NUMBER);
WaterLevelSensor    waterlevel_sensor   (WATER_LEVEL_SENSOR_PIN);
RainSensor          rain_sensor         (RAIN_SENSOR_PIN);

// Setup function, executed once on startup
void setup() {
  Serial.begin(SERIAL_COMMUNICATION_BAUD_RATE); // Initialize serial communication
  sms_module.init();
}

// Main loop function, continuously reads sensor values and prints them
void loop() {
  // Read sensor values
  AnalogSensorResult <RainIntensityType> rainintensity = rain_sensor.read(); // Read rain sensor
  AnalogSensorResult <WaterLevelType> waterlevel = waterlevel_sensor.read(); // Read water level sensor

  Serial.print(rainintensity.analog_value);
  Serial.print(' ');
  Serial.print(static_cast<int>(rainintensity.type));

  Serial.print(" | ");

  Serial.print(waterlevel.analog_value);
  Serial.print(' ');
  Serial.println(static_cast<int>(waterlevel.type));

  delay(1000);
}
