#include "Arduino.h"
#include "map.h"
#include "bullet.h"
#include "player.h"

Position playerPosition;

const int blinkDelay = 200;
static unsigned long lastBlink;

char playerOrientation = 'u';
int playerLife = 100;
int playerPower = 0;

unsigned long lastLifeDecrement;
const int lifeDecrementDelay = 100;

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

void incresePlayerLife(int points) {
    playerLife = min(100, playerLife + points);
}

void incresePlayerPower(int power) {
    playerPower += power;
}

void processPlayerInfo() {
    processPlayerLife();
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
