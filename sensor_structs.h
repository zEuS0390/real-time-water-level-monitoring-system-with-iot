#ifndef SENSOR_STRUCTS_H
#define SENSOR_STRUCTS_H

#include "sensor_enums.h"

template <typename T>
struct AnalogSensorResult {
  unsigned int analog_value = 0;
  T type = T::_NULL;
};

#endif