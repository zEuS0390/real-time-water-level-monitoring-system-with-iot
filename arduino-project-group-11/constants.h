#ifndef CONFIG_H
#define CONFIG_H

// Define constants for configuration
#define SERIAL_COMMUNICATION_BAUD_RATE      9600
#define SMS_MODULE_RX_PIN                   10
#define SMS_MODULE_TX_PIN                   11
#define SMS_MODULE_PHONE_NUMBER             "+639682495455"
#define SMS_MODULE_BAUD_RATE                9600
#define LIQUID_CRYSTAL_I2C_ADDRESS          0x27
#define LIQUID_CRYSTAL_NUMBER_OF_COLUMNS    16
#define LIQUID_CRYSTAL_NUMBER_OF_ROWS       2
#define WATER_LEVEL_SENSOR_PIN              A0
#define RAIN_SENSOR_PIN                     A3
#define RAIN_HEAVY_THRESHOLD                300
#define WATER_EMPTY_THRESHOLD               0
#define WATER_LOW_THRESHOLD                 350
#define WATER_MEDIUM_THRESHOLD              450
#define WATER_HIGH_THRESHOLD                1023

#endif
