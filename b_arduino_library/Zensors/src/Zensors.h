#include <Arduino.h>

namespace Zensors {

  // Template struct to hold the result
  template <typename T>
  struct Result {
    int value = 0;	// Holds a value, and its default is 0
    T type = T::_NULL;	// Represents the type or status of the result, the default value is T::_NULL
  };

  // Enum to represent different intensities of rain
  enum class RainIntensityType {
    _NULL,    // None
    _HEAVY,   // Heavy rain
    _LIGHT    // Light rain
  };

  // Enum to represent different water levels
  enum class WaterLevelType {
    _NULL,      // None
    _EMPTY,     // Empty water level
    _LOW,       // Low water level
    _MEDIUM,    // Medium water level
    _HIGH,      // High water level,
    _CRITICAL   // Critical water level
  };

  // Enum to represent different distances
  enum class DistanceType {
    _NULL
  };

  // Function to convert RainIntensityType enum to string
  const char* enumToString(RainIntensityType);

  // Function to convert WaterLevelType enum to string
  const char* enumToString(WaterLevelType);

  // Base class for analog sensors
  template <size_t MaxPins>
  class AnalogSensor {
  protected:
    unsigned int analog_pins[MaxPins]; // Use a fixed-size array to store pins
    size_t num_pins; // Track the number of pins

  public:
    // Constructor to initialize digital pins
    template<typename... Args>
    AnalogSensor(Args... pins) : num_pins(sizeof...(pins)) {
        static_assert(sizeof...(pins) == MaxPins, "Too many pins specified");
        unsigned int pinsArray[] = {pins...};
        for (size_t i = 0; i < num_pins; ++i) {
            analog_pins[i] = pinsArray[i];
        }
    }

    // // Method to initialize pinMode in setup function
    template <typename... Modes>
    void init(Modes... modes) {
        static_assert(sizeof...(modes) == MaxPins, "Number of modes exceeds MaxPins");

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

  // Base class for digital sensors
  template <size_t MaxPins>
  class DigitalSensor {
  protected:
    unsigned int digital_pins[MaxPins]; // Use a fixed-size array to store pins
    size_t num_pins; // Track the number of pins

  public:
    // Constructor to initialize digital pins
    template <typename... Args>
    DigitalSensor(Args... pins) : num_pins(sizeof...(pins)) {
        static_assert(sizeof...(pins) == MaxPins, "Too many pins specified");
        unsigned int pinsArray[] = {pins...};
        for (size_t i = 0; i < num_pins; ++i) {
            digital_pins[i] = pinsArray[i];
        }
    }

    // Method to initialize pinMode in setup function
    template <typename... Modes>
    void init(Modes... modes) {
        static_assert(sizeof...(Modes) <= MaxPins, "Number of modes exceeds MaxPins");

        int modeArr[] = {modes...};

        for (size_t i = 0; i < sizeof...(Modes); ++i) {
            pinMode(digital_pins[i], modeArr[i]);
        }
    }

    // Method to read digital value from the sensor
    unsigned int read(unsigned int pinIndex) {
        if (pinIndex < num_pins) {
            return digitalRead(digital_pins[pinIndex]);
        } else {
            // Handle invalid index
            return 0;
        }
    }
  };

  class RainSensor: public AnalogSensor<1> {
  public:
    // Constructor to initialize rain sensor with pin number
  RainSensor(const unsigned int);
  Result <RainIntensityType> read();
  // Method to read rain intensity from the sensor
  Result <RainIntensityType> read(unsigned int);
  };

  // Subclass for ultrasonic sensor, inherits from DigitalSensor
  class UltrasonicSensor : public DigitalSensor<2> {
  public:
    // Constructor to initialize ultrasonic sensor with pin numbers
    UltrasonicSensor(const unsigned int, const unsigned int);
    Result <DistanceType> read();
  };

  // Subclass for water level sensor, inherits from AnalogSensor
  class WaterLevelSensor : public AnalogSensor<4> {
  public:
    // Constructor to initialize analog pin
    WaterLevelSensor(const unsigned int, 
                     const unsigned int,
                     const unsigned int,
                     const unsigned int);

    Result <WaterLevelType> read();
  };
}
