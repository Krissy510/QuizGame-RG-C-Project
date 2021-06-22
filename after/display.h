#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define ARRAY_SIZE 256

struct User {
    char username[ARRAY_SIZE];
    char password[ARRAY_SIZE];
    double score;
    int allq;
    int correctq;
    int wrongq;
};

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
    else if(strcmp(color_name,"yellow") == 0){
        printf("\033[0;33m");
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

void delay(double number_of_seconds)
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

void guide(int mode) {
    // mode = 0 menu
    // mode = 1 editor
    if(mode == 0){
        printf("Introduction:\nKris's PG quiz game is a quiz game that was built to resemble an online-quizgame\n");
        printf("or you could this program to help you memorize some topic easier while being entertainment.\n");
        system("pause");
        system("cls");
        printf("Gameplay:\n");
        printf("(1)Normal Quiz Game\nScore: x1\nA gamemode that is straight forward enough.\n");
        printf("Its the game mode where it will ask question and give you\n4 choices to choose which 1 of them is the only answer.\n");
        system("pause");
        system("cls");
        printf("(2)Type it out!\nScore: x4\n");
        printf("This game mode purpose was to train you for all the quizgame and what is the best way to\n");
        printf("Train your memorization by typing it out!\n\n");
        system("pause");
        system("cls");
        printf("(3)Blink of an eye\nScore: x3.5\n");
        printf("Also similar to normal quiz game but this time it will force your memorization to the limit!\n");
        printf("In this gamemode the program will display a question and 4 choices for only 3 seconds then dissapear after the time\n");
        printf("Then you will try to enter the correct answer.\n");
        system("pause");
        system("cls");
        color("yellow");
        printf("Hope you enjoy the game!\n");
        color("reset");
        system("pause");
        system("cls");
    }
    if(mode == 1){
        printf("Editor:\n\nEdit\n-Where you can edit the topic or Q&A\n\n");
        printf("Force Change Password\n-Change user password\n\n");
        printf("Clear/Remove\n-Clear or Remove user data\n\n");
        system("pause");
        system("cls");
    }
    
}

int user_choice(char *text, int min_val, int max_val) { //choice format with /back func
    char choice[ARRAY_SIZE];
    while (1) {
        printf("%s", text);
        gets(choice);
        system("cls");
        if (strcmp(choice, "/back") == 0 || strcmp(choice, "/quit") == 0 )// if the user wants to go back
            return -1;
        int check = atoi(choice);
        if (check <= max_val && check >= min_val)
            return check;
        else{
            color("red");
            printf("Please enter only in the given choice\n");
            color("reset");
        }
    }
}

void dis_user_info(char given_user[]) {
    struct User temp;
    strcpy(temp.username, given_user);
    load_score(&temp);
    color("cyan");
    printf("Username: %s\n", temp.username);
    color("reset");
    printf("Total_score: %.2lf\n", temp.score);
    printf("All Q: %d\n", temp.allq);
    color("green");
    printf("Correct Q: %d\n", temp.correctq);
    color("red");
    printf("Wrong Q: %d\n", temp.wrongq);
    color("reset");
}

void dis_current_info(struct User givenGuest){
    color("yellow");
    printf("Current\n");
    color("cyan");
    printf("Username: %s\n", givenGuest.username);
    color("reset");
    printf("Total_score: %.2lf\n", givenGuest.score);
    printf("All Q: %d\n", givenGuest.allq);
    color("green");
    printf("Correct Q: %d\n", givenGuest.correctq);
    color("red");
    printf("Wrong Q: %d\n", givenGuest.wrongq);
    color("reset");
}

void error_message(int type){
    if(type == 0){
        color("red");
        printf("Please enter only in the given choice\n");
        color("reset");
    }
    else if(type == 1){
        color("red");
        printf("User does not exist.\n");
        color("reset");
    }
}