#include "Arduino.h"
#include "EEPROM.h"

const int buzzerPin = 13;
const bool silentModeMemoryAddress = 2;

void setupBuzzer() {
    pinMode(buzzerPin, OUTPUT);
}

bool isSilentMode() {
    bool silentMode;
    EEPROM.get(silentModeMemoryAddress, silentMode);
    return silentMode;
}

void changeSilentMode(bool silentMode) {
    EEPROM.put(silentModeMemoryAddress, silentMode);
}

void menuSound() {
    if (isSilentMode() == false)
        tone(buzzerPin, 400, 200);
}

void selectionSound() {
    if (isSilentMode() == false)
        tone(buzzerPin, 800, 150);
}

void shootSound() {
    if (isSilentMode() == false) {
        tone(buzzerPin, 500, 50);
    }
}

void shotgunShootSound() {
    if (isSilentMode() == false) {
        tone(buzzerPin, 400, 70);
    }
}
