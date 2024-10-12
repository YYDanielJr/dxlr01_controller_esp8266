#include "dxlr01.h"

String DXLR01::readline()
{
    String ret;
    char lastlast = 0;
    char last = 0;
    char current = 0;
    while (!(lastlast == '\r' && last == '\n'))
    {
        current = Serial.read();
        ret += current;
        lastlast = last;
        last = current;
        current = 0;
    }
    return ret;
}

bool DXLR01::testModule() {
    size_t num = Serial.write("+++\r\n");
    String recv = readline();
    if (recv.equals("Entry AT\r\n")) {
        size_t num2 = Serial.write("+++\r\n");
        String recv2 = readline();
        if (recv2.equals("Exit AT\r\n")) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
    return false;
}