#include "game.h"

struct player me = {2, 19};
int enemiesHealths[20][4];
int shots[20][4];

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
}

void goRight(){
    if(me.x < 3){
        strcpy(array[me.y][me.x], " ");
        me.x++;
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
}

void updateShots(){
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 4; j++)
            if(shots[i][j] > 0){
                if(enemiesHealths[i][j] > 0){
                    enemiesHealths[i][j] -= 1;
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