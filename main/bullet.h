#ifndef BULLET.H
#define BULLET.H
#include "map.h"

void showBullets();

void shoot(Position playerPosition, char direction);

void setShotgunMode(bool);

void resetBullets();

#endif
