#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

// Base class for analog sensors
class AnalogSensor {
private:
    unsigned int analog_pin;

public:
    // Constructor to initialize analog pin
    AnalogSensor(const unsigned int pin) : analog_pin(pin) {}

    // Method to read analog value from the sensor
    unsigned int read() {
        return analogRead(analog_pin); 
    }
};

#endif
