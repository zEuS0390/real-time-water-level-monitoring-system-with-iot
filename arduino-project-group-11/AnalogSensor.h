#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "sensor_structs.h"

// Base class for analog sensors
template<size_t MaxPins>
class AnalogSensor {
protected:
    unsigned int analog_pins[MaxPins]; // Use a fixed-size array to store pins
    size_t num_pins; // Track the number of pins

public:
    // Constructor to initialize digital pins
    template<typename... Args>
    AnalogSensor(Args... pins) : num_pins(sizeof...(pins)) {
        static_assert(sizeof...(pins) <= MaxPins, "Too many pins specified");
        unsigned int pinsArray[] = {pins...};
        for (size_t i = 0; i < num_pins; ++i) {
            analog_pins[i] = pinsArray[i];
        }
    }

    // // Method to initialize pinMode in setup function
    template<typename... Modes>
    void init(Modes... modes) {
        static_assert(sizeof...(Modes) <= MaxPins, "Number of modes exceeds MaxPins");

        int modeArr[] = {modes...};

        for (size_t i = 0; i < sizeof...(Modes); ++i) {
            pinMode(analog_pins[i], modeArr[i]);
        }
    }

    // // Method to read analog value from the sensor
    unsigned int read(unsigned int pinIndex) {
        if (pinIndex < num_pins) {
            return analogRead(analog_pins[pinIndex]);
        } else {
            // Handle invalid index
            return 0;
        }
    }
};

#endif
