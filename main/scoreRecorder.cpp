#include <EEPROM.h>
#include "Arduino.h"

const int numberScoresSaved = 5;
const int firstScoreMemoryAddress = 100;
const int firstNameMemoryAddress = 200;
const int nameSize = 12;
const int scoreSize = 2;

int getValueFromMemory(int memoryAddress) {
    int value;
    EEPROM.get(memoryAddress, value);
    return value;
}

int getScorePosition(int score) {
    int position = 0;

    while (position < numberScoresSaved) {
        int scoreMemAd = firstScoreMemoryAddress + scoreSize * position;
        if (score > getValueFromMemory(scoreMemAd))
            break;
        position++;
    }
    return position;
}

void saveScoreOnEEPROM(int score, char name[nameSize]) {
    int position = getScorePosition(score);
    if (position < numberScoresSaved) {
        int scoreMemAd = firstScoreMemoryAddress + scoreSize * position;
        int nameMemAd = firstNameMemoryAddress + nameSize * position;
        EEPROM.put(scoreMemAd, score);
        EEPROM.put(nameMemAd, name);
    }
}

bool isOnPodium(int score) {
    int lastScoreMemAd = firstScoreMemoryAddress + scoreSize * (numberScoresSaved - 1);
    int value = getValueFromMemory(lastScoreMemAd);
    return score > value;
}

void resetHighscore() {
    for (int i = 0; i < numberScoresSaved; i++) {
        EEPROM.put(firstScoreMemoryAddress + scoreSize * i, 0);
    }
}
