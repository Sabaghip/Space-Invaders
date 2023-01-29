#include "game.h"

struct player me = {2, 19};
int enemiesHealths[20][4];
//0 for not special or 2 healts, 1 for faster shots
int enemiesType[20][4];
int shots[20][4];
int enemyShots[20][4];

int enemiesTime = 0;
int enemiesCount = 0;
int enemyRowCounter = 0;


void delay(int d){
    clock_t temp = clock() + d;
    while(temp > clock()); 
}

void arrayInit(){
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 4; j++)
            strcpy(array[i][j] , " ");

    for(int i = 0; i < 20; i++){
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
    for(int i = 0; i < 3; i++){
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
    for(int i = 0; i < 20; i++){
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
    for(int i = 0; i < 20; i++){
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
    updateEnemiesOnArray();
    updateShotsOnArray();
    updateMeOnArray();
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 4; j++){
            printf("%s ", array[i][j]);
        }
        printf("\n");
    }
    printf("Health : %d    enemies : %d\n", me.health, enemiesCount);
}

void updateShots(){
    for(int i = 0; i < 20; i++){
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
                    }
                    shots[i][j] = 0;
                    continue;
                }
                strcpy(array[i][j], " ");
                shots[i][j] = 0;
                if(i > 0){
                    shots[i - 1][j] = 1;
                }
            }
        }
    }
    for(int i = 19; i >= 0; i--){
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
                if(i < 19){
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
                if(i < 18){
                    enemyShots[i + 2][j] = 2;
                }
            }
        }
    }
}

void updateEnemies(){
    for(int i = 19; i >= 0; i--){
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
            enemiesHealths[0][j] = 1;
            enemiesType[0][j] = 0;
        }
        else{
            if(j % 2 == 0){
                enemiesHealths[0][j] = 2;
                enemiesType[0][j] = 0;
            }
            else{
                enemiesHealths[0][j] = 1;
                enemiesType[0][j] = 1;
            }
        }
    }
    enemyRowCounter++;
}

void loose(){
    printf("loose!!!"color_reset);
    exit(1);
}

void win(){
    printf("win!!!"color_reset);
    exit(1);
}

void enemyshot(){
    for(int i = 18; i >= 0; i--){
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

void playEasy(){
    enemiesTime = 5;
    me.health = 7;
    enemiesCount = 15;
    loop();
}
void playNormal(){
    enemiesTime = 3;
    me.health = 5;
    enemiesCount = 25;
    loop();
}
void playHard(){
    enemiesTime = 1;
    me.health = 3;
    enemiesCount = 35;
    loop();
}