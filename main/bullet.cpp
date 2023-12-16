#include "bullet.h"
#include "player.h"
#include "Arduino.h"
#include "sound.h"

const int blinkDelay = 30;
static unsigned long lastBlink;

const int moveDelay = 150;
unsigned long lastMove;

Position bulletPosition;
bool validBullet;
Position shotgunBulletPosition[3];
bool validShotgunBullet[3];

char direction = 'n';

int numberShotgunShoots = 3;

void changeBulletPosition() {
    if (!validBullet)
        return;
    gameMap[bulletPosition.line][bulletPosition.column] = 0;
    bulletPosition.line += 1 * (direction == 'd') -1 * (direction == 'u');
    bulletPosition.column += 1 * (direction == 'r') -1 * (direction == 'l');

    if (!isOnMap(bulletPosition)) {
        validBullet = false;
        return;
    }
    if (isWall(bulletPosition)) {
        destroyWallSound();
        increasePlayerLife(1);
        increasePlayerPower(1);
        increasePlayerScore(1);
        gameMap[bulletPosition.line][bulletPosition.column] = 0;
        validBullet = false;
    }
}

void changeShotgunBulletsPositions() {
    for (int i = 0; i < 3; i++) {
        if (!validShotgunBullet[i])
            continue;
        gameMap[shotgunBulletPosition[i].line][shotgunBulletPosition[i].column] = 0;
        shotgunBulletPosition[i].line += 1 * (direction == 'd') -1 * (direction == 'u') + (i - 1) * (direction == 'r' || direction == 'l');
        shotgunBulletPosition[i].column += 1 * (direction == 'r') -1 * (direction == 'l') + (i - 1) * (direction == 'd' || direction == 'u');

        if (!isOnMap(shotgunBulletPosition[i])) {
            validShotgunBullet[i] = false;
            continue;
        }
        if (isWall(shotgunBulletPosition[i])) {
            destroyWallSound();
            increasePlayerLife(1);
            increasePlayerScore(3);
            gameMap[shotgunBulletPosition[i].line][shotgunBulletPosition[i].column] = 0;
            validShotgunBullet[i] = false;
        }
    }
}

void showBullets() {
    if (millis() - lastBlink > blinkDelay) {
        if (validBullet)
            gameMap[bulletPosition.line][bulletPosition.column] = 1 - gameMap[bulletPosition.line][bulletPosition.column];
        for (int i = 0; i < 3; i++)
            if (validShotgunBullet[i])
                gameMap[shotgunBulletPosition[i].line][shotgunBulletPosition[i].column] = 1 - gameMap[shotgunBulletPosition[i].line][shotgunBulletPosition[i].column];
        lastBlink = millis();
    }
    if (millis() - lastMove > moveDelay) {
        changeBulletPosition();
        changeShotgunBulletsPositions();
        lastMove = millis();
    }
}

bool activeShoot() {
    for (int i = 0; i < 3; i++)
        if (validShotgunBullet[i])
            return true;
    return validBullet;
}


void normalShoot(Position playerPosition, char playerOrientation) {
    if (!activeShoot()) {
        bulletPosition = playerPosition;
        validBullet = true;
        direction = playerOrientation;
    }
}

void shotgunShoot(Position playerPosition, char playerOrientation) {
    for (int i = 0; i < 3; i++) {
        shotgunBulletPosition[i] = playerPosition;
        validShotgunBullet[i] = true;
    }
    direction = playerOrientation;
}

void shoot(Position playerPosition, char playerOrientation) {
    if (!activeShoot()) {
        if (numberShotgunShoots) {
            shotgunShoot(playerPosition, playerOrientation);
            shotgunShootSound();
            numberShotgunShoots--;
        }
        else {
            normalShoot(playerPosition, playerOrientation);
            shootSound();
        }
    }
}

void activateShotgunMode() {
    numberShotgunShoots = 3;
}

void resetBullets() {
    validBullet = false;
    for (int i = 0; i < 3; i++)
        validShotgunBullet[i] = false;
    numberShotgunShoots = 0;
}

int getNumberShotgunShoots() {
    return numberShotgunShoots;
}
