#include "bullet.h"
#include "player.h"
#include "Arduino.h"

const int blinkDelay = 30;
static unsigned long lastBlink;

const int moveDelay = 150;
unsigned long lastMove;

Position bulletPosition;
bool validBullet;
Position shotgunBulletPosition[3];
bool validShotgunBullet[3];

char direction = 'n';

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
        incresePlayerLife(1);
        incresePlayerPower(1);
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
            incresePlayerLife(1);
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


void shoot(Position playerPosition, char playerOrientation) {
    if (!activeShoot()) {
        bulletPosition = playerPosition;
        validBullet = true;
        direction = playerOrientation;
    }
}

void shotgunShoot(Position playerPosition, char playerOrientation) {
    if (!activeShoot()) {
        for (int i = 0; i < 3; i++) {
            shotgunBulletPosition[i] = playerPosition;
            validShotgunBullet[i] = true;
        }
        direction = playerOrientation;
    }
}
