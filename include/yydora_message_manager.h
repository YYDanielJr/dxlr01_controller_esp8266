#pragma once
#include <Arduino.h>
#include "dxlr01.h"
#include "yydora_parser.h"

class YYDoraMessageManager {
private:
    DXLR01* loraModule;
public:
    YYDoraMessageManager(DXLR01* module) {
        loraModule = module;
    }

    bool send(String text) {
        loraModule->write((yydoraParser(text) + "\r\n").c_str());
        return true;
    }


};