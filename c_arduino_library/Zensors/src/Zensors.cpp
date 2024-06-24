#include <Zensors.h>

namespace Zensors {

  // Function to convert RainIntensityType enum to string
  const char* enumToString(RainIntensityType intensity) {
      switch (intensity) {
          case RainIntensityType::_NULL: return "NULL";
          case RainIntensityType::_HEAVY: return "HEAVY";
          case RainIntensityType::_LIGHT: return "LIGHT";
          default: return "UNKNOWN";
      }
  }

  // Function to convert WaterLevelType enum to string
  const char* enumToString(WaterLevelType level) {
      switch (level) {
          case WaterLevelType::_NULL: return "NULL";
          case WaterLevelType::_EMPTY: return "EMPTY";
          case WaterLevelType::_LOW: return "LOW";
          case WaterLevelType::_MEDIUM: return "MEDIUM";
          case WaterLevelType::_HIGH: return "HIGH";
          case WaterLevelType::_CRITICAL: return "CRITICAL";
          default: return "UNKNOWN";
      }
  }

  RainSensor::RainSensor(const unsigned int pin): AnalogSensor(pin) {}

  Result <RainIntensityType> RainSensor::read() {
    Result <RainIntensityType> rainsensor;
    rainsensor.value = AnalogSensor<1>::read(0);
    return rainsensor;
  }

  // Method to read rain intensity from the sensor
  Result <RainIntensityType> RainSensor::read(
    unsigned int rain_heavy_threshold
  ) {
    Result <RainIntensityType> rainintensity;
    const int analog_value = AnalogSensor<1>::read(0);
    rainintensity.value = analog_value;

    // Categorize rain intensity based on threshold
    if (analog_value < rain_heavy_threshold)
      rainintensity.type = RainIntensityType::_HEAVY;
    else {
      rainintensity.type = RainIntensityType::_LIGHT;
    }
    return rainintensity;
  }

  // Constructor to initialize ultrasonic sensor with pin numbers
  UltrasonicSensor::UltrasonicSensor(const unsigned int trig_pin, const unsigned int echo_pin): 
    DigitalSensor(trig_pin, echo_pin) {}

  Result <DistanceType> UltrasonicSensor::read() {
    digitalWrite(this->digital_pins[0], HIGH);
    delayMicroseconds(2);
    digitalWrite(this->digital_pins[0], LOW);
    delayMicroseconds(10);
    const long duration = pulseIn(this->digital_pins[1], HIGH);
    const int measured_distance = duration * 0.034 / 2;
    Result <DistanceType> distance;
    distance.value = measured_distance;
    return distance;
  }

  // Constructor to initialize analog pin
  WaterLevelSensor::WaterLevelSensor(const unsigned int water_level1_pin, 
                                     const unsigned int water_level2_pin,
                                     const unsigned int water_level3_pin,
                                     const unsigned int water_level4_pin)
    : AnalogSensor(water_level1_pin, water_level2_pin, water_level3_pin, water_level4_pin) {}

  Result <WaterLevelType> WaterLevelSensor::read() {
    Result <WaterLevelType> waterlevel;
    const int water_level1_analog_value = AnalogSensor<4>::read(0);
    const int water_level2_analog_value = AnalogSensor<4>::read(1);
    const int water_level3_analog_value = AnalogSensor<4>::read(2);
    const int water_level4_analog_value = AnalogSensor<4>::read(3);
    if (water_level4_analog_value >= 300) {
      waterlevel.type = WaterLevelType::_CRITICAL;
    }
    else if (water_level3_analog_value >= 300) {
      waterlevel.type = WaterLevelType::_HIGH;
    }
    else if (water_level2_analog_value >= 300) {
      waterlevel.type = WaterLevelType::_MEDIUM;
    }
    else if (water_level1_analog_value >= 300) {
      waterlevel.type = WaterLevelType::_LOW;
    } else {
      waterlevel.type = WaterLevelType::_EMPTY;
    }
    return waterlevel;
  }
}
