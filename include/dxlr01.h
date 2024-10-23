#pragma once
#include <Arduino.h>

class DXLR01 {
private:
    String readline();
    bool testModule();

public:
    bool isAvailable;
    DXLR01(unsigned long baud) {
        Serial.begin(baud);
        // isAvailable = testModule();
        isAvailable = true;
    }

    size_t write(String text) {
        return Serial.print((text + "\r\n").c_str());
    }
};