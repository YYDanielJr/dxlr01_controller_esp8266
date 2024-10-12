#pragma once
#include <ErriezCRC32.h>
#include <Arduino.h>

class ReceivedPackage {
private:
    bool valid;
    int targetDevice;
    int packageType;
    int packageNumber;
    int longPackageNumber;
    String text;

public:
    ReceivedPackage(bool valid, int device, int type, int number, int longPackageNumber, String text) {
        this->valid = valid;
        this->targetDevice = device;
        this->packageType = type;
        this->packageNumber = number;
        this->longPackageNumber = longPackageNumber;
        this->text = text;
    }

    bool isValid() {
        return valid;
    }

    int getTargetDevice() {
        return targetDevice;
    }

    int getPackageType() {
        return packageType;
    }

    int getPackageNumber() {
        return packageNumber;
    }

    int getLongPackageNumber() {
        return longPackageNumber;
    }

    String getText() {
        return text;
    }
};

int getPackageCount();
String generateShortPackage(String text);
String yydoraConfirmParser(int packageNumber, int longPackageNumber);
String yydoraResendRequestParser(int packageNumber, int longPackageNumber);
String yydoraParser(String text);
ReceivedPackage yydoraUnparser(String text);