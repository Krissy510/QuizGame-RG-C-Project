#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "check.h"
#include "dataManager.h"
#define ARRAY_SIZE 256

//UTILITY

void get_pass(char passw[]) { // ask and encrypt the password
    char ch;
    int i = 0;
    while (1) {
        ch = getch();
        if (ch == 13 || ch == 9) { //Enter = 13 Tab = 9
            passw[i] = '\0';
            break;
        }
        else if (ch == 8) {//backspace = 8
            if (i > 0) {
                i--;   // decrement so that the new character will overwrite
                printf("\b \b"); // \b = del the character before in display
            }
        }
        else {
            passw[i++] = ch;
            printf("*");
        }
    }
    printf("\n");
}


//Take
//Register
int take_username_reg(char *returnuser) { //ask user to for their username
    printf("Use only alphabet or numbers.\n");
    printf("If you want to go back enter '/back'\n");
    printf("Username:");
    gets(returnuser); // ask for a new user name
    if (strcmp(returnuser, "/back") == 0)  // if user want to go back to the choosing of login regis or guest
        return -1;
    if (check_user_exist(returnuser) == 1 || check_contain_sp(returnuser) == 1 || strlen(returnuser) == 0)
        while (1) {
            system("cls");
            color("red");
            printf("Error!\n");
            if (check_user_exist(returnuser) == 1)
                printf("The user is already exist!\n");
            else if (check_contain_sp(returnuser) == 1)
                printf("Please use only alphabet or numbers.\n");
            else if(strlen(returnuser) == 0)
                printf("Username cannot be empty.\n");
            color("reset");
            printf("If you want to go back enter '/back'\n");
            printf("Username:");
            gets(returnuser);
            if (strcmp(returnuser, "/back") == 0)
                return -1;
            if (check_user_exist(returnuser) == 0 && check_contain_sp(returnuser) == 0 && strlen(returnuser) != 0){ 
                break;
            }
        }
    system("cls");
    return 1; // finish process
}

int take_password_reg(char *return_password) {
    char temp[ARRAY_SIZE];
    while (1) { //big loop if user want to go back from confirmation stage
        while (1) {
            pass_syntax_guide();// Display the format that how the password should be
            printf("If you want to go back enter '/back'\n");
            printf("Password:");
            get_pass(return_password); //Ask user for a pass word then decrypt it
            system("cls"); // Screen cleared
            if (strcmp(return_password, "/back") == 0)// if the user wants to go back to the username part
                return -1;
            else if (check_pass_syntax(return_password) == 1 && check_contain_sp(return_password) == 0)
                break; //it will process to the next loop
            else {
                color("red");
                printf("ERROR:\n");
                if (check_pass_syntax(return_password) == 0)
                    printf("Invalid password format.\n");
                else if (check_contain_sp(return_password) == 1)
                    printf("Password should not contain any special characters.\n");
                color("reset");
            }

        }
        while (1) {
            printf("If you want to go back enter '/back'\n");
            printf("Confirm password: ");
            get_pass(temp);
            if (strcmp(temp, "/back") == 0) {
                system("cls"); // It will break out from this loop and go back to the asking password loop again
                break;
            }
            else if (strcmp(temp, return_password) == 0) { // if password match
                system("cls");
                return 1; // end of this func
            }
            else{ // if not matched then it will still loop until user enter match or enter /back
                system("cls");
                color("red");
                printf("Incorrect\n");
                color("reset");
            }
        }
    }
}

//Login
int take_username_log(char *returnuser) { //Ask user username for login
    while (1) {
        color("reset");
        printf("If you want to go back enter '/back'\n");
        printf("Username:");
        gets(returnuser);
        system("cls");
        if (strcmp(returnuser, "/back") == 0) // return user back to rlg
            return -1;
        else if (check_user_exist(returnuser) == 1 && check_contain_sp(returnuser) == 0)
            break;
        else{
            color("red");
            if (check_user_exist(returnuser) == 0)
                printf("This user does not exist!\n");
            else if (check_contain_sp(returnuser) == 1)
                printf("Please use only alphabet or numbers.\n");
        }
    }
    return 1; //Finished
}

int take_password_log(char username[], char return_password[]) { //Ask user password for login
    while (1) {
        printf("If you want to go back enter '/back'\n");
        printf("Username:%s\n", username);
        printf("Password:");
        get_pass(return_password);
        system("cls");
        if (strcmp(return_password, "/back") == 0)
            return -1;
        else if(check_match(username,return_password) == 1){
            break;
        }
        else{
            color("red");
            printf("Incorrect please try again\n");
            color("reset");
        }
    }
    return 1;
}


//main function
int registerUser(struct User *givenUser){
    while(1){
        if (take_username_reg(givenUser->username) == -1) //go back to rlg
            return -1;
        else if (take_password_reg(givenUser->password) == -1) //go back to username reg
            system("cls");
        else // take password and user name has been succeed
            break;
    }
    givenUser->score = 0;
    givenUser->allq = 0;
    givenUser->correctq = 0;
    givenUser->wrongq = 0;
    regis_user_data(givenUser->username,givenUser->password);
    color("green");
    printf("Succesfully register user as %s\n", givenUser->username);
    color("reset");
    delay(1);
    return 1;
}

int login(struct User *givenUser){
    
    while (1) { // loop for getting user and password
        if (take_username_log(givenUser->username) == -1)
            return -1; //user wants to go back to entry page
        else if (take_password_log(givenUser->username, givenUser->password) == -1)
            system("cls");//user wants to go back to take username login
        else{ // The format of username or password is correct
            break;
        }
    }
    load_score(givenUser);
    color("green");
    printf("Succesfully login user as %s\n", givenUser->username);
    color("reset");
    delay(1);
    return 1;
}

void guest(struct User *givenUser){
    strcpy(givenUser->username, "Guest");
    givenUser->score = 0;
    givenUser->allq = 0;
    givenUser->correctq = 0;
    givenUser->wrongq = 0;
    color("green");
    printf("Succesfully login user as Guest\n");
    color("reset");
    delay(1);
}
