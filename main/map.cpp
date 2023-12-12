#include "LedControl.h" 
#include <EEPROM.h>
#include "map.h"
#include "player.h"
#include "bullet.h"

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);
const int brightnessMemoryAddress = 2;
const int maxLevelBrightness = 14;
const int wallProbability = 10;
Position miniMapPosition;
bool gameMap[mapSize][mapSize];

void setupMatrix() {
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
            gameMap[i][j] = int(randomNumber < wallProbability);
        }
    miniMapPosition.line = 0;
    miniMapPosition.column = 0;
    generatePlayerPosition();
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

void showMatrix(const bool matrix[][matrixSize]) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            lc.setLed(0, i, j, matrix[i][j]);
        }
    }
}

void showEndGameMatrix() {
    const bool matrix[matrixSize][matrixSize] = {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    };
    showMatrix(matrix);
}


void showSettingsMatrix() {
    const bool matrix[matrixSize][matrixSize] = {
        { 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 1 },
        { 0, 0, 0, 1, 1, 1, 1, 1 },
        { 0, 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 0, 1, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 }
    };
    showMatrix(matrix);
}

void showGameMatrix() {
    const bool matrix[matrixSize][matrixSize] = {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
    };
    showMatrix(matrix);
}

void showAboutMatrix() {
    const bool matrix[matrixSize][matrixSize] = {
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 1, 0, 0 },
        { 0, 0, 1, 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0 },
    };
    showMatrix(matrix);
}
