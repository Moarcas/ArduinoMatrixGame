#include <EEPROM.h>
#include "Arduino.h"
#include "lcd.h"

const int numberScoresSaved = 5;
const int firstScoreMemoryAddress = 100;
const int firstNameMemoryAddress = 200;
const int nameSize = 11; // name + '\0'
const int scoreSize = 2;

int indexCurrentScore = 0;

int getScoreFromEEPROM(int indexScore) {
    int scoreMemAd = firstScoreMemoryAddress + scoreSize * indexScore;
    int value;
    EEPROM.get(scoreMemAd, value);
    return value;
}

String getNameFromEEPROM(int indexScore) {
    int nameMemAd = firstNameMemoryAddress + nameSize * indexScore;
    String name = "";
    char val;
    for (int i = 0; i < nameSize; i++) {
        val = EEPROM.read(nameMemAd + i);
        if (val == '\0')
            break;
        name += val;
    }
    return name;
}

void writeNameToEEPROM(int indexScore, String name) {
    int nameMemAd = firstNameMemoryAddress + nameSize * indexScore;
    for (int i = 0; i < name.length(); i++)
        EEPROM.put(nameMemAd + i, name[i]);
    EEPROM.put(nameMemAd + name.length(), '\0');
}

void writeScoreToEEPROM(int indexScore, int score) {
    int scoreMemAd = firstScoreMemoryAddress + scoreSize * indexScore;
    EEPROM.put(scoreMemAd, score);
}

int getScorePosition(int score) {
    int position = 0;

    while (position < numberScoresSaved) {
        if (score > getScoreFromEEPROM(position))
            break;
        position++;
    }
    return position;
}

void saveScore(int score, String name) {
    int position = getScorePosition(score);

    if (position >= numberScoresSaved)
        return;

    for (int i = numberScoresSaved - 2; i >= position; i--) {
        writeScoreToEEPROM(i + 1, getScoreFromEEPROM(i));
        writeNameToEEPROM(i + 1, getNameFromEEPROM(i));
    }

    writeScoreToEEPROM(position, score);
    writeNameToEEPROM(position, name);
}

bool isOnPodium(int score) {
    int value = getScoreFromEEPROM(numberScoresSaved - 1);
    return score > value;
}

void resetHighscore() {
    for (int i = 0; i < numberScoresSaved; i++) {
        writeScoreToEEPROM(i, 0);
        writeNameToEEPROM(i, "");
    }
}

void showHighscore() {
    int score = getScoreFromEEPROM(indexCurrentScore);
    String name = getNameFromEEPROM(indexCurrentScore);
    if (name == "")
        name = "None";
    lcdPrintHighscore(indexCurrentScore + 1, score, name);
}

void goToNextHighscore() {
    if (indexCurrentScore != numberScoresSaved - 1)
        indexCurrentScore++;
}

void goToPrevHighscore() {
    if (indexCurrentScore != 0)
        indexCurrentScore--;
}

void resetIndexHighscore() {
    indexCurrentScore = 0;
}
