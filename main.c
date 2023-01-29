#include "game.h"


void showAboutUs(){
    time_t t;
    while(1){
        system("cls");
        printf(color_red"Space-Invaders\n-----------------\nWritten By: Parsa Sabaghi\nGithub: Sabaghip"color_green"\n\nPRESS SPACE TO GO BACK\n"color_reset);
        time(&t);
        printf(color_blue"%s\r"color_reset, ctime(&t));
        delay(1000);
        if(kbhit()){
            if(getch() == 32){
                return;
            }
        }
    }
}

int mainMenu(){
    system("cls");
    printf(color_green"select:\n 1.start\n 2.about us\n 3.exit"color_reset);
    while(1){
        int temp = getch();
        switch(temp){
            case KEY_1:
                return 1;
            case KEY_2:
                return 2;
            case KEY_3:
                exit(1);
        }
    }
}

void getName(){
    system("cls");
    printf(color_green"Enter your name : "color_reset);
    scanf("%s", name);
}

void getDificalty(){
    system("cls");
    printf(color_green"Dificulty ?\n1. Easy\n2. Normal\n3.Hard"color_reset);
    while(1){
        switch(getch()){
            case KEY_1:
                playEasy();
                break;
            case KEY_2:
                playNormal();
                break;
            case KEY_3:
                playHard();
                break;
        }
    }
}

int main(){
    while(1){
        int choice = mainMenu();
        if(choice == 1){
            getName();
            getDificalty();
        }
        else{
            showAboutUs();
        }
    }

    return 0;
}