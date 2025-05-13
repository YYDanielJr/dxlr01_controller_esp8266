#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

class DXLR01 {
private:
    String readline();
    bool testModule();
    SoftwareSerial *softwareSerial;

public:
    bool isAvailable;
    DXLR01(unsigned long baud) {
        Serial.begin(baud);
        softwareSerial = nullptr;
        // isAvailable = testModule();
        isAvailable = true;
    }

    DXLR01(unsigned long baud, int rxPin, int txPin) {
        softwareSerial = new SoftwareSerial(rxPin, txPin);
        softwareSerial->begin(baud);
        // isAvailable = testModule();
        isAvailable = true;
    }

    size_t write(String text) {
        if (softwareSerial) {
            return softwareSerial->print((text + "\r\n").c_str());
        } else {
            return Serial.print((text + "\r\n").c_str());
        }
    }
};