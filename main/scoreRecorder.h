#ifndef SCORERECORDER.H
#define SCORERECORDER.H


bool isOnPodium(int score);

void saveScoreOnEEPROM(int score, String name);

void resetHighscore();

void showHighscore();

void goToNextHighscore();

void goToPrevHighscore();

#endif
