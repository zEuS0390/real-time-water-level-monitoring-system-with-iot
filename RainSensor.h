#ifndef RAINSENSOR_H
#define RAINSENSOR_H

#include "constants.h"
#include "AnalogSensor.h"
#include "sensor_structs.h"

class RainSensor : public AnalogSensor {
public:
    RainSensor(const unsigned int pin) : AnalogSensor(pin) {}

    AnalogSensorResult <RainIntensityType> read() {
      AnalogSensorResult <RainIntensityType> rainintensity ;
      const int analog_value = AnalogSensor::read();
      rainintensity.analog_value = analog_value;
      if (analog_value < RAIN_HEAVY_THRESHOLD)
        rainintensity.type = RainIntensityType::_HEAVY;
      return rainintensity;
    }
};

#endif
