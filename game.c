#include "game.h"


const int Y_UP = 0;
const int Y_DOWN = 17;
struct player me = {2, Y_DOWN - 1};
int enemiesHealths[20][4];
//0 for not special or 2 healts, 1 for faster shots
int enemiesType[20][4];
int shots[20][4];
int enemyShots[20][4];

int enemiesTime = 0;
int enemiesCount = 0;
int enemyRowCounter = 0;
int enemiesCountTemp = 0;


void delay(int d){
    clock_t temp = clock() + d;
    while(temp > clock()); 
}

void arrayInit(){
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 4; j++)
            strcpy(array[i][j] , " ");

    for(int i = Y_UP; i < Y_DOWN; i++){
        for(int j = 0; j < 4; j++){
            if(enemiesType[i][j] == 1){
                strcpy(array[i][j], color_red"^");
            }
            else if(enemiesHealths[i][j] == 2){
                strcpy(array[i][j], color_purple"*");
            }
            else if(enemiesHealths[i][j] == 1){
                strcpy(array[i][j], color_red"*");
            }
        }
    }
    strcpy(array[me.y][me.x], color_green"U");
}

void gameInit(){
    for(int i = Y_UP; i < Y_UP + 3; i++){
        enemyRowCounter++;
        for(int j = 0; j < 4; j++){
            if(i % 2 == 0){
                enemiesHealths[i][j] = 1;
                enemiesType[i][j] = 0;
            }
            else{
                if(j % 2 == 0){
                    enemiesHealths[i][j] = 2;
                    enemiesType[i][j] = 0;
                }
                else{
                    enemiesHealths[i][j] = 1;
                    enemiesType[i][j] = 1;
                }
            }
        }
    }
    arrayInit();
}

void goLeft(){
    if(me.x > 0){
        strcpy(array[me.y][me.x], " ");
        me.x--;
        strcpy(array[me.y][me.x], color_green"U");
    }
    else{
        strcpy(array[me.y][me.x], " ");
        me.x = 3;
        strcpy(array[me.y][me.x], color_green"U");
    }
}

void goRight(){
    if(me.x < 3){
        strcpy(array[me.y][me.x], " ");
        me.x++;
        strcpy(array[me.y][me.x], color_green"U");
    }
    else{
        strcpy(array[me.y][me.x], " ");
        me.x = 0;
        strcpy(array[me.y][me.x], color_green"U");
    }
}

void shoot(){
    shots[me.y][me.x] = 1;
}

void checkKeyboard(){
    int temp = getch();
    switch(temp){
        case KEY_1:
            exit(1);
            break;
        case KEY_A:
            goLeft();
            break;
        case KEY_D:
            goRight();
            break;
        case KEY_SPACE:
            shoot();
            break;
    }
}

void updateShotsOnArray(){
    for(int i = Y_UP; i < Y_DOWN; i++){
        for(int j = 0; j < 4; j++){
            if(shots[i][j] > 0){
                strcpy(array[i][j], color_blue"*");
            }
            if(enemyShots[i][j] > 0){
                strcpy(array[i][j], color_green"*");
            }
        }
    }
}

void updateEnemiesOnArray(){
    for(int i = Y_UP; i < Y_DOWN; i++){
        for(int j = 0; j < 4; j++){
            if(enemiesType[i][j] == 1){
                strcpy(array[i][j], color_red"^");
            }
            else if(enemiesHealths[i][j] == 2){
                strcpy(array[i][j], color_purple"*");
            }
            else if(enemiesHealths[i][j] == 1) {
                strcpy(array[i][j], color_red"*");
            }
        }
    }
}

void updateMeOnArray(){
    strcpy(array[me.y][me.x], color_green"U");
}

void updateLCD(){
    system("cls");
    printf(color_reset"Health : %d    enemies : %d\n", me.health, enemiesCount);
    if(me.health == 1){
        printf(color_red"YOU HAVE ONE HEALTH!!!\n"color_reset);
    }
    else{
        printf("\n");
    }
    if(enemiesCount <= 3){
        printf(color_green"JUST %d MORE ENEMIES TO WIN\n"color_reset, enemiesCount);
    }
    else{
        printf("\n");
    }
    updateEnemiesOnArray();
    updateShotsOnArray();
    updateMeOnArray();
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 4; j++){
            printf("%s   ", array[i][j]);
        }
        printf("\n");
    }
}

void updateShots(){
    for(int i = Y_UP; i < Y_DOWN; i++){
        for(int j = 0; j < 4; j++){
            if(shots[i][j] > 0){
                if(enemiesHealths[i][j] > 0){
                    enemiesHealths[i][j] -= 1;
                    if(enemiesHealths[i][j] == 0){
                        enemiesCount--;
                        if(enemiesCount == 0){
                            win();
                        }
                        strcpy(array[i][j], " ");
                        enemiesType[i][j] = 0;
                    }
                    shots[i][j] = 0;
                    continue;
                }
                strcpy(array[i][j], " ");
                shots[i][j] = 0;
                if(i > Y_UP){
                    shots[i - 1][j] = 1;
                }
            }
        }
    }
    for(int i = Y_DOWN - 1; i >= Y_UP; i--){
        for(int j = 0; j < 4; j++){
            if(enemyShots[i][j] == 1){
                if(me.x == j && me.y == i){
                    me.health--;
                    if(me.health == 0){
                        loose();
                    }
                    strcpy(array[i][j], " ");
                    enemyShots[i][j] = 0;
                    continue;
                }
                strcpy(array[i][j], " ");
                enemyShots[i][j] = 0;
                if(i < Y_DOWN - 1){
                    enemyShots[i + 1][j] = 1;
                }
            }
            else if(enemyShots[i][j] == 2){
                if(me.x == j && (me.y == i || me.y == i + 1)){
                    me.health--;
                    if(me.health == 0){
                        loose();
                    }
                    strcpy(array[i][j], " ");
                    enemyShots[i][j] = 0;
                    continue;
                }
                strcpy(array[i][j], " ");
                enemyShots[i][j] = 0;
                if(i < Y_DOWN - 2){
                    enemyShots[i + 2][j] = 2;
                }
            }
        }
    }
}

void updateEnemies(){
    for(int i = Y_DOWN - 1; i >= Y_UP; i--){
        for(int j = 0; j < 4; j++){
            if(enemiesHealths[i][j] > 0){
                if(i == 19){
                    loose();
                    return;
                }
                enemiesHealths[i + 1][j] = enemiesHealths[i][j];
                enemiesType[i + 1][j] = enemiesType[i][j];
                enemiesHealths[i][j] = 0;
                enemiesType[i][j] = 0;
            }
        }
    }
    for(int j = 0; j < 4; j++){
        if(enemyRowCounter % 2 == 0){
            enemiesHealths[Y_UP][j] = 1;
            enemiesType[Y_UP][j] = 0;
        }
        else{
            if(j % 2 == 0){
                enemiesHealths[Y_UP][j] = 2;
                enemiesType[Y_UP][j] = 0;
            }
            else{
                enemiesHealths[Y_UP][j] = 1;
                enemiesType[Y_UP][j] = 1;
            }
        }
    }
    enemyRowCounter++;
}

void loose(){
    system("cls");
    printf(color_red"\n\tYou lost the game.\n\tyou killed %d enemies\n\tthere was still %d enemies left!\n\tgood luck next time."color_reset,enemiesCountTemp - enemiesCount, enemiesCount);
    exit(1);
}

void win(){
    system("cls");
    printf(color_green"\n\tYou won the game.\n\tgood job."color_reset);
    exit(1);
}

void enemyshot(){
    for(int i = Y_DOWN - 2; i >= Y_UP; i--){
        if(enemiesHealths[i][me.x] > 0){
            if(enemiesType[i][me.x] == 1){
                enemyShots[i + 1][me.x] = 2;
            }
            else{
                enemyShots[i + 1][me.x] = 1;
            }
            return;
        }
    }
}

void loop(){
    gameInit();
    int i = 1;
    updateLCD();
    int timeForEnemy = (int)(enemiesTime * 50); 
    int timeForEnemyShot = timeForEnemy * 2;
    while(1){
        int j = 0;
        if(kbhit()){
            checkKeyboard();
            j++;
        }
        if(i % 7 == 0){
            updateShots();
            j++;
        }
        if(i % timeForEnemy == 0){
            updateEnemies();
            j++;
        }
        if(i % timeForEnemyShot == 0){
            enemyshot();
            j++;
        }
        if(j){
            updateLCD();
        }
        i++;
        if(i > 2000){
            i=0;
        }
        delay(5);
    }
};

void printDetails(char dificulty[]){
    system("cls");
    printf("\n\t difficalty = %s\n\tyou should kill %d enemies\n\tPRESS SPACE TO START", dificulty, enemiesCount);
    while(1){
        if(getch() == KEY_SPACE){
            break;
        }
    }
}

void playEasy(){
    enemiesTime = 5;
    me.health = 7;
    enemiesCount = 15;
    enemiesCountTemp = 15;
    printDetails("Easy");
    loop();
}
void playNormal(){
    enemiesTime = 3;
    me.health = 5;
    enemiesCount = 25;
    enemiesCountTemp = 25;
    printDetails("Normal");
    loop();
}
void playHard(){
    enemiesTime = 1;
    me.health = 3;
    enemiesCount = 35;
    enemiesCountTemp = 35;
    printDetails("Hard");
    loop();
}