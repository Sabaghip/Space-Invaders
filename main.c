#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#include "key.h"

void loop(){};

void delay(int d){
    clock_t temp = clock() + d;
    while(temp > clock()); 
}

void showAboutUs(){
    time_t t;
    while(1){
        system("cls");
        printf("Space-Invaders\n-----------------\nWritten By: Parsa Sabaghi\nGithub: Sabaghip\n\nPRESS SPACE TO GO BACK\n");
        time(&t);
        printf("%s\r", ctime(&t));
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
    printf("select:\n 1.start\n 2.about us\n 3.exit");
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

int main(){
    while(1){
        int choice = mainMenu();
        if(choice == 1){
            loop();
        }
        else{
            showAboutUs();
        }
    }

    return 0;
}