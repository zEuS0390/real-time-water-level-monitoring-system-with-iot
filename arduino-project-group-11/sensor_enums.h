#ifndef SENSOR_ENUMS_H
#define SENSOR_ENUMS_H

// Enum to represent different intensities of rain
enum class RainIntensityType {
  _NULL,    // None
  _HEAVY,   // Heavy rain
  _LIGHT    // Light rain
};

// Enum to represent different water levels
enum class WaterLevelType {
  _NULL,    // None
  _EMPTY,   // Empty water level
  _LOW,     // Low water level
  _MEDIUM,  // Medium water level
  _HIGH     // High water level
};

// Enum to represent different distances
enum class DistanceType {
  _NULL
};

#endif
