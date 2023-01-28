#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#include "key.h"
#include "game.h"

void loop(){};

void delay(int d){
    clock_t temp = clock() + d;
    while(temp > clock()); 
}

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
    loop();
}

int main(){
    while(1){
        int choice = mainMenu();
        if(choice == 1){
            getName();
        }
        else{
            showAboutUs();
        }
    }

    return 0;
}