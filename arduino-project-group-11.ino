#include "constants.h"
#include "sensor_enums.h"
#include "sensor_structs.h"
#include "RainSensor.h"
#include "WaterLevelSensor.h"
#include "SMSModule.h"

WaterLevelSensor    waterlevel_sensor  (WATER_LEVEL_SENSOR_PIN);
RainSensor          rain_sensor        (RAIN_SENSOR_PIN);

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_BAUD_RATE);
}

void loop() {

  AnalogSensorResult <RainIntensityType> rainintensity = rain_sensor.read();
  AnalogSensorResult <WaterLevelType> waterlevel = waterlevel_sensor.read();

  Serial.print(rainintensity.analog_value);
  Serial.print(' ');
  Serial.print(static_cast<int>(rainintensity.type));

  Serial.print(" || ");

  Serial.print(waterlevel.analog_value);
  Serial.print(' ');
  Serial.println(static_cast<int>(waterlevel.type));

  delay(1000);
}
