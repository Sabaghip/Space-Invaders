#include "game.h"

struct player me = {2, 19};
int enemiesHealths[20][4];
int shots[20][4];

int enemiesTime = 0;
int enemiesCount = 0;

void arrayInit(){
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 4; j++)
            strcpy(array[i][j] , " ");

    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 4; j++)
            if(enemiesHealths[i][j] > 0){
                strcpy(array[i][j], color_red"*");
            }
    strcpy(array[me.y][me.x], color_green"U");
}

void gameInit(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            enemiesHealths[i][j] = 1;
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
        case 49:
            exit(1);
            break;
        case 97:
            goLeft();
            break;
        case 100:
            goRight();
            break;
        case 32:
            shoot();
            break;
    }
}

void updateShotsOnArray(){
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 4; j++)
            if(shots[i][j] > 0){
                strcpy(array[i][j], color_blue"*");
            }
}

void updateEnemiesOnArray(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 4; j++){
            if(enemiesHealths[i][j] > 0){
                strcpy(array[i][j], color_red"*");
            }
            else{
                strcpy(array[i][j], " ");
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
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 4; j++)
            if(shots[i][j] > 0){
                if(enemiesHealths[i][j] > 0){
                    enemiesHealths[i][j] -= 1;
                    if(enemiesHealths[i][j] == 0){
                        enemiesCount--;
                        if(enemiesCount == 0){
                            win();
                        }
                    }
                    shots[i][j] = 0;
                    continue;
                }
                strcpy(array[i][j], " ");
                shots[i][j] = 0;
                if(i >= 0){
                    shots[i - 1][j] = 1;
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
                enemiesHealths[i][j] = 0;
            }
        }
    }
    for(int j = 0; j < 4; j++){
        enemiesHealths[0][j] = 1;
    }
}

void loose(){
    printf("loose!!!"color_reset);
    exit(1);
}

void win(){
    printf("win!!!"color_reset);
    exit(1);
}

void loop(){
    gameInit();
    int i = 1;
    updateLCD();
    int timeForEnemy = (int)(enemiesTime * 50); 
    while(1){
        int j = 0;
        if(kbhit()){
            checkKeyboard();
            j++;
        }
        if(i % 5 == 0){
            updateShots();
            j++;
        }
        if(i % timeForEnemy == 0){
            updateEnemies();
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