#include "yydora_parser.h"
#define DEVICE_ADDRESS "1001"

int packageCount = 0;
int packageCutLength = 512;

int getPackageCount() {
    packageCount = packageCount + 1;
    if (packageCount >= 10000) {
        packageCount = 0;
    }
    return packageCount;
}

String generateShortPackage(String text) {
    String headMagicNumber = "1145";
    String tailMagicNumber = "1919";
    String ret;
    ret = headMagicNumber + DEVICE_ADDRESS + "0";
    char pc[6] = {0};
    sprintf(pc, "%04d", getPackageCount());
    ret += pc;
    ret = ret + "0000" + text + tailMagicNumber;
    return ret;
}

String yydoraConfirmParser(int packageNumber, int longPackageNumber) {
    String package = "1145";
    package = package + DEVICE_ADDRESS + "5";
    char pn[6] = {0};
    char lpn[6] = {0};
    sprintf(pn, "%04d", packageNumber);
    sprintf(lpn, "%04d", longPackageNumber);
    package = package + pn + lpn + "1919";
    return package;
}

String yydoraResendRequestParser(int packageNumber, int longPackageNumber) {
    String package = "1145";
    package = package + DEVICE_ADDRESS + "2";
    char pn[6] = {0};
    char lpn[6] = {0};
    sprintf(pn, "%04d", packageNumber);
    sprintf(lpn, "%04d", longPackageNumber);
    package = package + pn + lpn + "1919";
    return package;
}

String yydoraParser(String text) {
    if(text.length() <= packageCutLength) {
        String packageStr = generateShortPackage(text);
        char pl[5] = {0};
        sprintf(pl, "%03d", packageStr.length());
        String package = pl + packageStr;
        package += crc32String(package.c_str());
        return package;
    }
    return String();
}

// 从begin到end-1
int sliceToInt(String text, int begin, int end) {
    char slice[end - begin + 1] = {0};
    for(int i = 0; begin <= end; i++, begin++) {
        slice[i] = text.charAt(begin);
    }
    return atoi(slice);
}

// 从begin到end-1
String slice(String text, int begin, int end) {
    char _slice[end - begin + 1] = {0};
    for(int i = 0; begin <= end; i++, begin++) {
        _slice[i] = text.charAt(begin);
    }
    return String(_slice);
}

ReceivedPackage yydoraUnparser(String text) {
    int textPointer = 0;
    int packageLength = sliceToInt(text, 0, 3);
    int crcPart = sliceToInt(text, packageLength + 3, text.length());
    String packagePart = slice(text, 0, packageLength + 3);
    if(crcPart == crc32String(packagePart.c_str())) {
        int targetDevice = sliceToInt(text, 7, 11);
        int packageType = sliceToInt(text, 11, 11);
        int packageNumber = sliceToInt(text, 12, 16);
        int longPackageNumber = sliceToInt(text, 16, 20);
        int mainTextSize = packageLength - 21;
        String mainText = slice(text, 20, 20 + mainTextSize);
        return ReceivedPackage(true, targetDevice,packageType, packageNumber, longPackageNumber, mainText);
    } else {
        return ReceivedPackage(false, 0, 0, 0, 0, "");
    }
}
