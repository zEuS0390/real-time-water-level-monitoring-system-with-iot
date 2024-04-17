#ifndef RAINSENSOR_H
#define RAINSENSOR_H

#include "constants.h"
#include "AnalogSensor.h"
#include "sensor_structs.h"

class RainSensor: public AnalogSensor<1> {
public:
    // Constructor to initialize rain sensor with pin number
  RainSensor(const unsigned int pin): AnalogSensor<1>(pin) {}

  // Method to read rain intensity from the sensor
  Result <RainIntensityType> read() {
    Result <RainIntensityType> rainintensity;
    const int analog_value = AnalogSensor<1>::read(0);
    rainintensity.value = analog_value;

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
