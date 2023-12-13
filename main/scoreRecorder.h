#ifndef SCORERECORDER.H
#define SCORERECORDER.H

bool isOnPodium(int score);

void saveScoreOnEEPROM(int score, char name[]);

void resetHighscore();

#endif
