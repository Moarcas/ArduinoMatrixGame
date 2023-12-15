#include "Arduino.h"
#include "map.h"
#include "bullet.h"
#include "player.h"
#include "scoreRecorder.h"
#include "sound.h"

Position playerPosition;

const int blinkDelay = 200;
static unsigned long lastBlink;

char playerOrientation = 'u';
int playerLife = 100;
int playerPower = 0;
int playerScore = 0;

int level = 1;

const byte maxLife = 100;
const byte maxPower = 5;

unsigned long lastLifeDecrement;
int lifeDecrementDelay = 500;

const int nameMaxLength = 11; // name + '\0'
String name = "a";

void generatePlayerPosition() {
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++)
            if (!gameMap[i][j]) {
                playerPosition = (Position){i, j};
                return;
            }
}

void showPlayer() {
    if (millis() - lastBlink > blinkDelay) {
        gameMap[playerPosition.line][playerPosition.column] = 1 - gameMap[playerPosition.line][playerPosition.column];
        lastBlink = millis();
    }
}

void movePlayer(char direction) {
    Position nextPlayerPosition = playerPosition;

    nextPlayerPosition.line += 1 * (direction == 'd') -1 * (direction == 'u');
    nextPlayerPosition.column += 1 * (direction == 'r') -1 * (direction == 'l');

    if (isOnMap(nextPlayerPosition) && !isWall(nextPlayerPosition)) {
        gameMap[playerPosition.line][playerPosition.column] = 0;
        playerPosition = nextPlayerPosition;
    }
    playerOrientation = direction;
}

void processPlayerLife() {
    if (playerLife && millis() - lastLifeDecrement > lifeDecrementDelay) {
        playerLife--;
        lastLifeDecrement = millis();
    }
}

void processLevel() {
    if (level * 50 < playerScore) {
        levelUpSound();
        level++;
        lifeDecrementDelay -= 80;
        playerLife = 100;
    }
}

void resetPlayerInfo() {
    playerLife = 100;
    playerScore = 0;
    playerPower = 0;
    lifeDecrementDelay = 500;
    level = 1;
    name = "a";
    resetBullets();
}

void increasePlayerLife(int points) {
    playerLife = min(maxLife, playerLife + points);
}

void increasePlayerPower(int power) {
    playerPower = min(maxPower, playerPower + power);

    if (playerPower == maxPower) {
        activateShotgunMode();
        playerPower = 0;
    }
}

void increasePlayerScore(int points) {
    playerScore += points;
}

void processPlayerInfo() {
    processPlayerLife();
    processLevel();
}

Position getPlayerPosition() {
    return playerPosition;
}

char getPlayerOrientation() {
    return playerOrientation;
}

int getPlayerLife() {
    return playerLife;
}

int getPlayerPower() {
    return playerPower;
}

int getPlayerScore() {
    return playerScore;
}

String getPlayerName() {
    return name;
}

void playerNameDeleteLastChar() {
    if (name.length() == 1)
        return;
    name.remove(name.length() - 1);
}

void playerNameNextChar() {
    unsigned int indexCurrentChar = name.length() - 1;
    if (name[indexCurrentChar] == 'z')
        name[indexCurrentChar] = 'a';
    else
        name[indexCurrentChar] += 1;
}

void playerNamePrevChar() {
    unsigned int indexCurrentChar = name.length() - 1;
    if (name[indexCurrentChar] == 'a')
        name[indexCurrentChar] = 'z';
    else
        name[indexCurrentChar] -= 1;
}

void playerNameAddChar() {
    if (name.length() + 1 == nameMaxLength)
        return;
    name += "a";
}

int getLevel() {
    return level;
}
