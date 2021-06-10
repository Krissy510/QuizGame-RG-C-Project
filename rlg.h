#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "check.h"
#include "dataManager.h"
#define ARRAY_SIZE 256

//register

int take_username_reg(char *returnuser) { //ask user to for their username
    printf("Use only alphabet or numbers.\n");
    printf("If you want to go back enter '/back'\n");
    printf("Username:");
    gets(returnuser); // ask for a new user name
    if (strcmp(returnuser, "/back") == 0)  // if user want to go back to the choosing of login regis or guest
        return -1;
    if (check_user_exist(returnuser) == 1 || check_contain_sp(returnuser) == 1)
        while (1) {
            system("cls");
            color("red");
            printf("Error!\n");
            if (check_user_exist(returnuser) == 1)
                printf("The user is already exist!\n");
            else if (check_contain_sp(returnuser) == 1)
                printf("Please use only alphabet or numbers.\n");
            color("reset");
            printf("If you want to go back enter '/back'\n");
            printf("Username:");
            gets(returnuser);
            if (strcmp(returnuser, "/back") == 0)
                return -1;
            if (check_user_exist(returnuser) == 0 && check_contain_sp(returnuser) == 0) // if all condition met then break
                break;
        }
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