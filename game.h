
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include "key.h"

char name[100];

char array[20][4][10];

struct player{
    int x;
    int y;
    int health;
};


void arrayInit();
void gameInit();
void goLeft();
void goRight();
void shoot();
void checkKeyboard();
void updateShotsOnArray();
void updateEnemiesOnArray();
void updateMeOnArray();
void updateLCD();
void updateShots();
void playEasy();
void playNormal();
void playHard();
void loop();
void loose();
void win();
void delay(int);
void enemyshot();
void printDetails(char[]);
void looseAnimation();
void winAnimation();
void startAnimation();
void autoLoop();
void autoMove();
void autoShoot();
void playAuto();
void bossFight();
void bossShot();
void bossMove();
void bossInit();
void playBoss();