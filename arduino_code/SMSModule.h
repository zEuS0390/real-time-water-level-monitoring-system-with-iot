#ifndef SMS_MODULE_H
#define SMS_MODULE_H

#include <SoftwareSerial.h> // Include the SoftwareSerial library for GSM module communication
#include "constants.h"

// Class for interfacing with the GSM module
class SMSModule {
public:
    // Constructor to initialize GSM module pins and phone number
    SMSModule(int rxPin, int txPin, String phoneNumber) : sim(rxPin, txPin), number(phoneNumber) {}

    void init() {
      sim.begin(SMS_MODULE_BAUD_RATE);
    }

    // Method to send an SMS message
    void sendMessage(const String& message) {
        sim.println("AT+CMGF=1");    // Sets the GSM Module in Text Mode
        delay(200);
        sim.print("AT+CMGS=\"");
        sim.print(number); // Mobile phone number to send message
        sim.println("\"");
        delay(200);
        sim.println(message);
        delay(100);
        sim.write(26); // ASCII code of CTRL+Z
        delay(200);
        _buffer = _readSerial();
    }

    // Method to receive SMS messages
    void receiveMessage() {
        Serial.println("SIM800L Read an SMS");
        sim.println("AT+CMGF=1");
        delay(200);
        sim.println("AT+CNMI=1,2,0,0,0"); // AT Command to receive a live SMS
        delay(200);
        Serial.println("Unread Message done");
    }

    // Method to make a call
    void callNumber() {
        sim.print(F("ATD"));
        sim.print(number);
        sim.print(F(";\r\n"));
        _buffer = _readSerial();
        Serial.println(_buffer);
    }

private:
    SoftwareSerial sim;     // Instance of SoftwareSerial for GSM communication
    int _timeout;           // Timeout for communication
    String _buffer;         // Buffer for storing received data
    String number;          // Phone number for SMS and call

    // Method to read data from serial buffer
    String _readSerial() {
        _timeout = 0;
        while (!sim.available() && _timeout < 12000) {
            delay(13);
            _timeout++;
        }
        if (sim.available()) {
            return sim.readString();
        }
        return "";
    }
};

#endif
