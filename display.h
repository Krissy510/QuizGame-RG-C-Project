#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

void color(char *color_name){ // color set
    if(strcmp(color_name,"green") == 0){
        printf("\033[0;32m");
    }
    else if(strcmp(color_name,"red") == 0){
        printf("\033[0;31m");
    }
    else if(strcmp(color_name,"cyan") == 0){
        printf("\033[0;36m");
    }
    else if(strcmp(color_name,"reset") == 0){
        printf("\033[0m");
    }
}

void welcome(char *username) { // show a warm welcome to the current user
    system("cls"); // Clear screen
    color("green");
    printf("Hello, ");
    color("reset");
    printf("%s\n", username); 
    color("cyan");
    printf("Welcome to Kris PG's quiz game!\n");
    color("reset");
}

void delay(int number_of_seconds)
{
    clock_t end_time;
    end_time =  clock() + (1000 * number_of_seconds); // Storing end time
    while (clock() < end_time); // Loop until current time match end time
}

void pass_syntax_guide() { //display the password correct syntax
    printf("Please enter 9 characters.\n");
    printf("Use only alphabet or numbers.\n");
    printf("It should contain at least 1 capital letter.\n");
    printf("It should contain at least 1 lower case letter.\n");
    printf("It should contain at least 1 digit.\n");
    color("red");
    printf("Password should not contain any special characters.\n");
    color("reset");
}

void end_message() {
    color("green");
    printf("Thank you for playing, see you next time!\n");
    color("reset");
}

void guide() {
    printf("Introduction:\nKris's PG quiz game is a quiz game that was built to resemble an online-quizgame.\n");
    printf("That includes userdata and rank that players can use to compete each other.\n");
    printf("Or you could this program to help you memorize some topic easier while being entertained.\n");
    printf("\nEdit:\nTo edit topic and Q&A please use the admin account which can be found in the same folder as the program.\n");
    printf("\nGameplay:\n(1)Normal Quiz Game(x1.00)\nA gamemode that is straight forward enough.\n");
    printf("Its the game mode where it will ask question and give you\n4 choices to choose which 1 of them is the only answer.\n");
    printf("If you answer correct you get points.\n\n(2)Time attack(x1.5)\n");
    printf("Similar to Normal quiz game but now every time it displays a question\nyou have only 3 seconds to answer the question correctly.\n");
    printf("You will get a score when you answer the question correctly and also\nwithin 3 seconds. Hard isn't it?\n");
    printf("However, you got 15% percent bonus of your score.\nHard = Rewarding?\n\n(3)Type it out!(x0.00)\n");
    printf("This game mode purpose was to train you for all the quizgame and what is the best way to\n");
    printf(" train your memorization than typing it out!\n\n(4)Blink of an eye(x2.00)\n");
    printf("Also similar to normal quiz game but this time it will force your memorization to the limit!\n");
    printf("In this gamemode when it display a question and 4 choices you have only to memorize what is \n");
    printf("the answer of the question is and answer it.\nBut as I said the harder it is the rewarding it is.\n");
    printf("Therefore, this gamemode will give you up to double of the amount of score that you get by\nplaying normal quiz game.\n");
}

int user_choice(char *text, int min_val, int max_val) { //choice format with /back func
    char choice[100];
    while (1) {
        printf("%s", text);
        printf("If you want to go back enter '/back'\n");
        gets(choice);
        system("cls");
        if (strcmp(choice, "/back") == 0)// if the user wants to go back
            return -1;
        if (strlen(choice) == 1) {
            int check = atoi(choice);
            if (check <= max_val && check >= min_val)
                return check;
        }
    }
}