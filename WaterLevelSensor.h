#ifndef WATERLEVELSENSOR_H
#define WATERLEVELSENSOR_H

#include "constants.h"
#include "AnalogSensor.h"
#include "sensor_structs.h"

// Subclass for water level sensor, inherits from AnalogSensor
class WaterLevelSensor : public AnalogSensor {
public:
    // Constructor to initialize analog pin
    WaterLevelSensor(const unsigned int pin) : AnalogSensor(pin) {}

    // Method to read water level from the sensor
    AnalogSensorResult <WaterLevelType> read() {
        AnalogSensorResult <WaterLevelType> waterlevel;
        const int analog_value = AnalogSensor::read();

        // Categorize water level based on thresholds
        waterlevel.analog_value = analog_value;
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
