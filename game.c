#include "game.h"


const int Y_UP = 0;
const int Y_DOWN = 17;
struct player me = {2, Y_DOWN - 1};
int enemiesHealths[20][4];
//0 for not special or 2 healts, 1 for faster shots
int enemiesType[20][4];
int shots[20][4];
int enemyShots[20][4];
int boss[20][4];

int enemiesTime = 0;
int enemiesCount = 0;
int enemyRowCounter = 0;
int enemiesCountTemp = 0;
int bossHealth = 10;


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
            else if(boss[i][j] == 1){
                strcpy(array[i][j], color_purple"#");
            }
        }
    }
    strcpy(array[me.y][me.x], color_green"U");
}

void gameInit(){
    srand(time(NULL));
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
            else if(boss[i][j] == 1){
                strcpy(array[i][j], color_purple"#");
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
    if(bossHealth > 0){
        printf(color_green"BOSS HEALTH : %d\n"color_reset, bossHealth);
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
    for(int i = Y_UP; i < Y_DOWN; i++){
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
                if(boss[i][j] == 1){
                    bossHealth--;
                    if(bossHealth == 0){
                        win();
                    }
                    shots[i][j] = 0;
                    continue;
                }
                if(enemiesHealths[i][j] > 0){
                    enemiesHealths[i][j] -= 1;
                    if(enemiesHealths[i][j] == 0){
                        enemiesCount--;
                        if(enemiesCount == 0){
                            playBoss();
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
                if(i == Y_DOWN - 1){
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
    looseAnimation();
    system("cls");
    printf(color_red"\n\tYou lost the game.\n\tyou killed %d enemies\n\tthere was still %d enemies left!\n\tgood luck next time."color_reset,enemiesCountTemp - enemiesCount, enemiesCount);
    exit(1);
}

void win(){
    winAnimation();
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

void autoMove(){
    for(int i = Y_UP; i < Y_DOWN; i++){
        if(enemyShots[i][me.x] > 0){
            if(rand() % 2 == 0){
                goRight();
            }
            else{
                goLeft();
            }
            return;
        }
    }
    int temp = rand();
    if(temp % 3 == 0){
        goRight();
    }
    else if(temp % 3 == 1){
        goLeft();
    }
}

void autoShoot(){
    for(int i = Y_UP; i < Y_DOWN; i++){
        if(enemiesHealths[i][me.x] > 0){
            if(rand() % 2 == 0){
                shoot();
            }
            return;
        }
    }
}

void autoLoop(){
    gameInit();
    int i = 1;
    updateLCD();
    int timeForEnemy = (int)(enemiesTime * 50); 
    int timeForEnemyShot = timeForEnemy * 2;
    int timeForAutoShoot = 9;
    int timeForAutoMove = 12;
    while(1){
        int j = 0;
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
        if(i % timeForAutoMove == 0){
            autoMove();
            j++;
        }
        if(i % timeForAutoShoot == 0){
            autoShoot();
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

void startAnimation(){
    for(int m = 0; m < 10; m++){
        system("cls");
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 16; j++){
                if((i < 10 + m - 1 && i > 10 - m - 1) || (j < m + 10 - 1 && j > 10 - m - 1)){
                    if(((i >= 4 && i <= 5 ) && ((j <= 5  && j >= 4) || (j >= 8 && j <= 9))) || (i == 8 && (j <= 12 && j >= 3))){
                        printf(" ");
                    }
                    else{
                        printf("0");
                    }
                }
                else{
                    printf("*");
                }
            }
            printf("\n");
        }
        delay(150);
    }
    for(int m = 0; m < 10; m++){
        system("cls");
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 16; j++){
                if((i < 10 + m - 1 && i > 10 - m - 1) || (j < m + 10 - 1 && j > 10 - m - 1)){
                    printf(" ");
                }
                else{
                    if(((i >= 4 && i <= 5 ) && ((j <= 5  && j >= 4) || (j >= 8 && j <= 9))) || (i == 8 && (j <= 12 && j >= 3))){
                        printf(" ");
                    }
                    else{
                        printf("*");
                    }
                }
            }
            printf("\n");
        }
        delay(150);
    }
}

void winAnimation(){
    printf(color_green"");
    for(int m = 0; m < 10; m++){
        system("cls");
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 16; j++){
                if((i < 10 + m - 1 && i > 10 - m - 1) || (j < m + 10 - 1 && j > 10 - m - 1)){
                    if(((i >= 4 && i <= 5 ) && ((j <= 5  && j >= 4) || (j >= 8 && j <= 9))) || (i == 8 && (j <= 12 && j >= 3))){
                        printf(" ");
                    }
                    else{
                        printf("0");
                    }
                }
                else{
                    printf("*");
                }
            }
            printf("\n");
        }
        delay(150);
    }
    printf(color_reset"");
}

void looseAnimation(){
    printf(color_red"");
    for(int m = 0; m < 10; m++){
        system("cls");
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 16; j++){
                if((i < 10 + m - 1 && i > 10 - m - 1) || (j < m + 10 - 1 && j > 10 - m - 1)){
                    if(((i >= 4 && i <= 5 ) && ((j <= 5  && j >= 4) || (j >= 8 && j <= 9))) || (i == 8 && (j <= 12 && j >= 3))){
                        printf(" ");
                    }
                    else{
                        printf("0");
                    }
                }
                else{
                    printf("*");
                }
            }
            printf("\n");
        }
        delay(150);
    }
    printf(color_reset"");
}

void printDetails(char dificulty[]){
    system("cls");
    printf("\n\t difficalty = %s\n\tyou should kill %d enemies\n\tPRESS SPACE TO START", dificulty, enemiesCount);
    while(1){
        if(getch() == KEY_SPACE){
            break;
        }
    }
}

void bossInit(){
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 4; j++){
            strcpy(array[i][j] , " ");
            shots[i][j] = 0;
            enemiesHealths[i][j] = 0;
            enemiesType[i][j] = 0;
            enemyShots[i][j] = 0;
        }
    srand(time(NULL));
    bossHealth = 10;
    for(int i = Y_UP + 2; i < Y_UP + 4; i++){
        for(int j = 1; j < 3; j++){
            boss[i][j] = 1;
        }
    }
}

void bossMove(){
    int temp = rand()%4;
    if(temp == 0){
        //go right
        for(int i = Y_UP; i < Y_DOWN; i++){
            if(boss[i][3] == 1){
                return;
            }
        }
        for(int i = Y_UP; i < Y_DOWN; i++){
            for(int j = 2; j >= 0; j--){
                if(boss[i][j] == 1){
                    boss[i][j] = 0;
                    strcpy(array[i][j], " ");
                    boss[i][j + 1] = 1;
                    strcpy(array[i][j + 1], color_purple"#");
                }
            }
        }
    }
    else if(temp == 1){
        //go left
        for(int i = Y_UP; i < Y_DOWN; i++){
            if(boss[i][0] == 1){
                return;
            }
        }
        for(int i = Y_UP; i < Y_DOWN; i++){
            for(int j = 1; j < 4; j++){
                if(boss[i][j] == 1){
                    strcpy(array[i][j], " ");
                    boss[i][j] = 0;
                    strcpy(array[i][j - 1], color_purple"#");
                    boss[i][j - 1] = 1;
                }
            }
        }
    }
    else if(temp == 2){
        //go down
        for(int i = 0; i < 4; i++){
            if(boss[Y_DOWN - 6][i] == 1){
                return;
            }
        }
        for(int i = Y_DOWN - 6; i >= Y_UP; i--){
            for(int j = 3; j >= 0; j--){
                if(boss[i][j] == 1){
                    boss[i][j] = 0;
                    strcpy(array[i][j], " ");
                    boss[i + 1][j] = 1;
                    strcpy(array[i + 1][j], color_purple"#");
                }
            }
        }
    }
    else if(temp == 3){
        //go up
        for(int i = 0; i < 4; i++){
            if(boss[Y_UP][i] == 1){
                return;
            }
        }
        for(int i = Y_UP; i <= Y_DOWN - 6; i++){
            for(int j = 3; j >= 0; j--){
                if(boss[i][j] == 1){
                    boss[i][j] = 0;
                    strcpy(array[i][j], " ");
                    boss[i - 1][j] = 1;
                    strcpy(array[i - 1][j], color_purple"#");
                }
            }
        }
        
    }
}

void bossShot(){
    for(int i = Y_DOWN - 5; i >= Y_UP; i--){
        if(boss[i][me.x] > 0){
            enemyShots[i + 1][me.x] = 2;
            return;
        }
    }
}

void bossFight(){
    bossInit();
    int i = 1;
    updateLCD();
    int timeForBossMove = (int)(enemiesTime * 30); 
    int timeForBossShoot = (int)(timeForBossMove * 1.5);
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
        if(i % timeForBossMove == 0){
            bossMove();
            j++;
        }
        if(i % timeForBossShoot == 0){
            bossShot();
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
}

void playEasy(){
    enemiesTime = 5;
    me.health = 7;
    enemiesCount = 15;
    enemiesCountTemp = 15;
    printDetails("Easy");
    startAnimation();
    loop();
}
void playNormal(){
    enemiesTime = 3;
    me.health = 5;
    enemiesCount = 25;
    enemiesCountTemp = 25;
    printDetails("Normal");
    startAnimation();
    loop();
}
void playHard(){
    enemiesTime = 1;
    me.health = 3;
    enemiesCount = 35;
    enemiesCountTemp = 35;
    printDetails("Hard");
    startAnimation();
    loop();
}
void playAuto(){
    enemiesTime = 1;
    me.health = 3;
    enemiesCount = 35;
    enemiesCountTemp = 35;
    printDetails("Hard");
    startAnimation();
    autoLoop();
}
void playBoss(){
    enemiesTime = 1;
    if(me.health == 0){
        me.health = 3;
    }
    startAnimation();
    bossFight();
}
