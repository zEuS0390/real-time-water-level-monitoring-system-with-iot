#ifndef RAINSENSOR_H
#define RAINSENSOR_H

#include "constants.h"
#include "AnalogSensor.h"
#include "sensor_structs.h"

// Subclass for rain sensor, inherits from AnalogSensor
class RainSensor : public AnalogSensor {
public:
  // Constructor to initialize analog pin
  RainSensor(const unsigned int pin) : AnalogSensor(pin) {}

  // Method to read rain intensity from the sensor
  AnalogSensorResult <RainIntensityType> read() {
    AnalogSensorResult <RainIntensityType> rainintensity ;
    const int analog_value = AnalogSensor::read();
    rainintensity.analog_value = analog_value;

    // Categorize rain intensity based on threshold
    if (analog_value < RAIN_HEAVY_THRESHOLD)
      rainintensity.type = RainIntensityType::_HEAVY;
    else {
      rainintensity.type = RainIntensityType::_LIGHT;
    }
    return rainintensity;
  }
};

#endif
