#ifndef PLAYER.H
#define PLAYER.H
#include "map.h"

void generatePlayerPosition();

void showPlayer();

void movePlayer(char direction);

void processPlayerInfo();

Position getPlayerPosition();

char getPlayerOrientation();

int getPlayerLife();

void incresePlayerLife(int);

void incresePlayerPower(int);

#endif
