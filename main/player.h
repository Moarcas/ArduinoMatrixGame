#ifndef PLAYER.H
#define PLAYER.H
#include "map.h"

void generatePlayerPosition();

void showPlayer();

void movePlayer(char direction);

void processPlayerInfo();

Position getPlayerPosition();

char getPlayerOrientation();

void resetPlayerInfo();

int getPlayerLife();

int getPlayerPower();

int getPlayerPoints();

void increasePlayerLife(int);

void increasePlayerPower(int);

void increasePlayerPoints(int);

#endif
