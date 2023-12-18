#include "LedControl.h"
#include <EEPROM.h>
#include "map.h"
#include "player.h"
#include "bullet.h"

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);
const int brightnessMemoryAddress = 6;
const int maxLevelBrightness = 14;
const int wallProbability = 30;
Position miniMapPosition;
bool gameMap[mapSize][mapSize];
unsigned long lastAddedWallTime;
const int addWallDelay = 500;
const int numberMatricesAnimation = 8;
const int delayMatrixAnimation = 120;
unsigned long lastMatrixMove;

void setupMatrix() {
    randomSeed(analogRead(0));
    lc.shutdown(0, false);
    lc.setIntensity(0, matrixGetBrightnessLevel());
    lc.clearDisplay(0);
}

void matrixChangeBrightnessLevel(int difference) {
    int brightnessLevel, newBrightnessLevel;
    EEPROM.get(brightnessMemoryAddress, brightnessLevel);
    newBrightnessLevel = brightnessLevel + difference;
    if (newBrightnessLevel >= 1 && newBrightnessLevel <= maxLevelBrightness) {
        EEPROM.put(brightnessMemoryAddress, newBrightnessLevel);
        lc.setIntensity(0, newBrightnessLevel);
    }
}

void matrixResetBrightness() {
    EEPROM.put(brightnessMemoryAddress, int(maxLevelBrightness / 2));
    lc.setIntensity(0, int(maxLevelBrightness / 2));
}

int matrixGetBrightnessLevel() {
    int brightnessLevel;
    EEPROM.get(brightnessMemoryAddress, brightnessLevel);
    return brightnessLevel;
}

void generateMap() {
    int randomNumber;
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++) {
            randomNumber = random(100);
            gameMap[i][j] = randomNumber < wallProbability;
        }
    miniMapPosition.line = 0;
    miniMapPosition.column = 0;
    generatePlayerPosition();
}

void addWallsOnMap() {
    if (millis() - lastAddedWallTime < addWallDelay)
        return;
    int line = random(mapSize);
    int column = random(mapSize);
    Position playerPosition = getPlayerPosition();
    if (playerPosition.line != line && playerPosition.column != column) {
        gameMap[line][column] = 1;
        lastAddedWallTime = millis();
    }
}

void showMap() {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            lc.setLed(0, i, j, gameMap[miniMapPosition.line + i][miniMapPosition.column + j]);
        }
    }
    showPlayer();
    showBullets();
}

bool isOnMap(Position position) {
    return position.line >= 0 && position.line < mapSize && position.column >= 0 && position.column < mapSize;
}

bool isWall(Position position) {
    return gameMap[position.line][position.column];
}

void changeMiniMapPosition(Position playerPosition, char direction) {
    bool canMoveLeft = (direction == 'l' && miniMapPosition.column && playerPosition.column - miniMapPosition.column < 2);
    bool canMoveUp = (direction == 'u' && miniMapPosition.line && playerPosition.line - miniMapPosition.line < 2);
    bool canMoveRight = (direction == 'r' && miniMapPosition.column + matrixSize != mapSize && miniMapPosition.column + matrixSize - playerPosition.column < 3);
    bool canMoveDown = (direction == 'd' && miniMapPosition.line + matrixSize != mapSize && miniMapPosition.line + matrixSize - playerPosition.line < 3);


    if (canMoveLeft) {
        miniMapPosition.column--;
        return;
    }
    if (canMoveUp) {
        miniMapPosition.line--;
        return;
    }
    if (canMoveRight) {
        miniMapPosition.column++;
        return;
    }
    if (canMoveDown) {
        miniMapPosition.line++;
        return;
    }
}

void showMatrix(const uint64_t matrix) {
    for (int i = 0; i < matrixSize; i++) {
        byte row = (matrix >> i * matrixSize) & 0xFF;
        for (int j = 0; j < matrixSize; j++) {
            lc.setLed(0, i, j, bitRead(row, j));
        }
    }
}

void showIntroMatrix() {
    static byte index = 0;
    static byte x = 1;
    const uint64_t matrices[] = {
        0x0000000000000000,
        0x8100000000000081,
        0xc3810000000081c3,
        0xe7c381000081c3e7,
        0xffe7c38181c3e7ff,
        0xffffe7c3c3e7ffff,
        0xffffffe7e7ffffff,
        0xffffffffffffffff
    };
    showMatrix(matrices[index]);
    if (millis() - lastMatrixMove > delayMatrixAnimation) {
        index += x;
        if (index == 7)
            x = -1;
        else if (index == 0)
            x = 1;

        lastMatrixMove = millis();
    }
}

void showEndGameMatrix(bool isOnPodium) {
    if (!isOnPodium) {
        showMatrix(0x00423c0000666600);
    } else {
        showMatrix(0x003c420000666600);
    }
}


void showSettingsMatrix() {
    static byte index = 0;
    static byte x = 1;
    const uint64_t matrices[] = {
        0x03050e7cf8981830,
        0x02050e7cf8181810,
        0x00040e7c78181800,
        0x00000c7c38180800,
        0x0000083c18080000,
        0x0000001808000000
    };
    showMatrix(matrices[index]);
    if (millis() - lastMatrixMove > delayMatrixAnimation) {
        index += x;
        if (index == 5)
            x = -1;
        else if (index == 0)
            x = 1;

        lastMatrixMove = millis();
    }
}

void showGameMatrix() {
    static byte index = 0;
    const uint64_t matrices[numberMatricesAnimation] = {
        0x0000081838180800,
        0x0000103070301000,
        0x00002060e0602000,
        0x000040c0c1c04000,
        0x0000808183818000,
        0x0000010307030100,
        0x000002060e060200,
        0x0000040c1c0c0400
    };
    showMatrix(matrices[index]);
    if (millis() - lastMatrixMove > delayMatrixAnimation) {
        index++;
        if (index == numberMatricesAnimation)
            index = 0;
        lastMatrixMove = millis();
    }
}

void showAboutMatrix() {
    static byte index = 0;
    static byte x = 1;
    const uint64_t matrices[] = {
        0x0200020204090906,
        0x040004040812120c,
        0x0800080810242418,
        0x1000101020484830,
        0x2000202040909060
    };
    showMatrix(matrices[index]);
    if (millis() - lastMatrixMove > delayMatrixAnimation) {
        index += x;
        if (index == 4)
            x = -1;
        else if (index == 0)
            x = 1;

        lastMatrixMove = millis();
    }
}

void showHighscoreMatrix() {
    static byte index = 0;
    static byte x = 1;
    const uint64_t matrices[] = {
        0x1e1e0c0c1e3f3f3f,
        0x3c3c18183c7e7e7e,
        0x7878303078fcfcfc
    };
    showMatrix(matrices[index]);
    if (millis() - lastMatrixMove > delayMatrixAnimation) {
        index += x;
        if (index == 2)
            x = -1;
        else if (index == 0)
            x = 1;

        lastMatrixMove = millis();
    }
}
