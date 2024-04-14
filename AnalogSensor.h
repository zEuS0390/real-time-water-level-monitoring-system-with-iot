#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

class AnalogSensor {
private:
    unsigned int analog_pin;

public:
    AnalogSensor(const unsigned int pin) : analog_pin(pin) {}

    unsigned int read() {
        return analogRead(analog_pin); 
    }
};

#endif
