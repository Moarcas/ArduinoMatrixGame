#ifndef BULLET.H
#define BULLET.H
#include "map.h"

void showBullets();

void shoot(Position playerPosition, char direction);

void activateShotgunMode();

void resetBullets();

int getNumberShotgunShoots();

#endif
