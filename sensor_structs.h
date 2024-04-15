#ifndef SENSOR_STRUCTS_H
#define SENSOR_STRUCTS_H

#include "sensor_enums.h"

// Template struct to hold the result of an analog sensor readings and types
template <typename T>
struct AnalogSensorResult {
  unsigned int analog_value = 0;    // Holds the analog value read by the sensor, the default value is 0
  T type = T::_NULL;                // Represents the type or status of the sensor reading, the default value is T::_NULL
};

#endif