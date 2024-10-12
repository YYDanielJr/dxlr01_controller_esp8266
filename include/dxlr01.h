#pragma once
#include <Arduino.h>

class DXLR01 {
private:
    bool isAvailable;
    String readline();
    bool testModule();

public:
    DXLR01(unsigned long baud) {
        Serial.begin(baud);
        isAvailable = testModule();
    }


};