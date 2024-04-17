#ifndef WATERLEVELSENSOR_H
#define WATERLEVELSENSOR_H

#include "constants.h"
#include "AnalogSensor.h"
#include "sensor_structs.h"

// Subclass for water level sensor, inherits from AnalogSensor
class WaterLevelSensor : public AnalogSensor<1> {
public:
    // Constructor to initialize analog pin
    WaterLevelSensor(const unsigned int pin) : AnalogSensor<1>(pin) {}

    // Method to read water level from the sensor
    Result <WaterLevelType> read() {
        Result <WaterLevelType> waterlevel;
        const int analog_value = AnalogSensor<1>::read(0);

        // Categorize water level based on thresholds
        waterlevel.value = analog_value;
        if (analog_value == WATER_EMPTY_THRESHOLD)
            waterlevel.type = WaterLevelType::_EMPTY;
        else if (analog_value > WATER_EMPTY_THRESHOLD && analog_value <= WATER_LOW_THRESHOLD)
            waterlevel.type = WaterLevelType::_LOW;
        else if (analog_value > WATER_LOW_THRESHOLD && analog_value < WATER_MEDIUM_THRESHOLD)
            waterlevel.type = WaterLevelType::_MEDIUM;
        else if (analog_value >= WATER_MEDIUM_THRESHOLD && analog_value <= WATER_HIGH_THRESHOLD)
            waterlevel.type = WaterLevelType::_HIGH;
        return waterlevel;
    }
};

#endif
