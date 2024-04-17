#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include "DigitalSensor.h"
#include "sensor_enums.h"

// Subclass for ultrasonic sensor, inherits from DigitalSensor
class UltrasonicSensor : public DigitalSensor<2> {
public:
    // Constructor to initialize ultrasonic sensor with pin numbers
    UltrasonicSensor(const unsigned int trig_pin, const unsigned int echo_pin):
      DigitalSensor<2>(trig_pin, echo_pin) {}

    Result <DistanceType> read() {
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
};

#endif
