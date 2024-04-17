#ifndef SENSOR_STRUCTS_H
#define SENSOR_STRUCTS_H

#include "sensor_enums.h"

// Template struct to hold the result
template <typename T>
struct Result {
  int value = 0;	// Holds a value, and its default is 0
  T type = T::_NULL;	// Represents the type or status of the result, the default value is T::_NULL
};

#endif
