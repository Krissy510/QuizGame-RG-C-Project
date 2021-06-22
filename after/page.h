/*
ID: 63011293
Name: Raviphas Sananpanichkul
Midterm Project
C PROGRAMMING
Teacher: Ukrit Watchareeruetai
University: King Mongkut's Institute of Technology Ladkrabang
*/

#include "subpage.h"

int playPage(char topicChoose[], int *qa_Amount, int *mode_Select){
    int process;
    while(1){
        process = askTopic(1);
        if(process == 0){ // loop
            continue;
        }
        else if(process == -1){ // quit to menu
            return -1;
        }
        else{  // next
            getTopic(process, topicChoose,1); // load topic name to string
            while (1)
            {
                *qa_Amount = countQ(topicChoose);
                process = askAmountQ(topicChoose, qa_Amount);
                if(process == 1){
                    while (1)
                    {
                        process = askMode(mode_Select);
                        if(process == -1){
                            break;
                        }
                        else if(process == 1){
                            return 1;
                        }
                    }
                }
                else if(process == -1){
                    break;
                }
            }
        }
    }
}

int entryPage(struct User *userPointer){
    int process;
    while(1){
        int choice = user_choice("[1]Register\n[2]Login\n[3]Guest\nEnter '/quit' to quit the program\n",1,3);
        if(choice == -1){
            return -1;
        }
        else if(choice == 1){
            process = registerUser(userPointer);
        }
        else if(choice == 2){
            process = login(userPointer);
        }
        else if(choice == 3){
            guest(userPointer);
            process = 1;
        }
        if(process == 1){
            break;
        }
    }
    if(strcmp("root", userPointer->username) == 0){
        welcome("Admin");
        system("pause");
        system("cls");
        return 2;
    }
    welcome(userPointer->username);
    system("pause");
    system("cls");
    return 1;
}

int menu(struct User *userPointer){
    char choice[ARRAY_SIZE];
    while (1) {
        color("cyan");
        printf("MENU\n");
        color("green");
        printf("Currently login as %s\n", userPointer->username);
        color("reset");
        printf("[1]Play\n[2]Guide\n[3]User Info\n[4]Change Account\n[5]Change password\n[6]Quit\n");
        gets(choice);
        system("cls");
        int check = atoi(choice);
        if (check <= 6 && check >= 1)
            return check;
        else{
            error_message(0);
        }
    }
}

void userInfo(struct User givenUser){
    char userSearch[ARRAY_SIZE];
    while(1){
        dis_current_info(givenUser);
        printf("Enter '/back' to go back to menu\nSearch:");
        gets(userSearch);
        if(strcmp("/back",userSearch) == 0){
            system("cls");
            return;
        }
        else if(check_user_exist(userSearch) == 0){
            error_message(1);
        }
        else{
            system("cls");
            dis_user_info(userSearch);
            system("pause");
        }
        system("cls");
    }   
}

void changePassword(struct User *userPointer){
    if(strcmp("Guest", userPointer->username) == 0){
        color("red");
        printf("Sorry, this mode was disable for Guest");
        color("reset");
        return;
    }
    if(take_password_log(userPointer->username, userPointer->password) == 1){
        if(take_password_reg(userPointer->password) == -1){
            return;
        }
        update_user(*userPointer, 1);
        color("green");
        printf("Successfully changed the password\n");
        color("reset");
        system("pause");
        system("cls");
    }
    else{
        return;
    }
}

int editorMenu(){
    char choice[ARRAY_SIZE];
    while (1) {
        color("cyan");
        printf("EDITOR\n");
        color("reset");
        printf("[1]Edit\n[2]Guide\n[3]Force Change Password\n[4]Clear/Remove\n[5]Change account\n[6]Quit\n");
        gets(choice);
        system("cls");
        int check = atoi(choice);
        if (check <= 6 && check >= 1)
            return check;
        else{
            error_message(0);
        }
    }
}

void forceChangePass(){
    struct User temp;
    while(1){
        printf("Enter '/back' to go back\n");
        color("green");
        printf("USER: ");
        gets(temp.username);
        color("reset");
        system("cls");
        if(strcmp(temp.username, "/back") == 0){
            return;
        }
        if(check_user_exist(temp.username) == 1){
            load_score(&temp);
            if(take_password_reg(temp.password) == 1){
                if(admin_confirmation() == 1){
                    update_user(temp,1);
                    color("green");
                    printf("Successfully change password of %s\n", temp.username);
                    color("reset");
                    return;
                }
            }
        }
        else{
            color("red");
            printf("INVALID:\nThe given user doesn't exist\n");
            color("reset");
        }
    }
}

void clear_remove_data(){
    char input[ARRAY_SIZE];
    while(1){
        printf("Enter '/back' to go back\n");
        printf("[1]Clear user score\n[2]Remove user data\n");
        gets(input);
        system("cls");
        if(strcmp(input, "/back") == 0){
            return;
        }
        if(strlen(input) == 1){
            int check = atoi(input);
            if(check >= 1 && check <= 2){
                struct User temp;
                while(1){
                    printf("Enter '/back' to go back\n");
                    color("green");
                    printf("USER: ");
                    gets(temp.username);
                    color("reset");
                    system("cls");
                    if(strcmp(temp.username, "/back") == 0){
                        break;
                    }
                    if(check_user_exist(temp.username) == 1){
                        if(admin_confirmation() == 1){
                            if(check == 1){
                                temp.score = 0;
                                temp.allq = 0;
                                temp.correctq = 0;
                                temp.wrongq = 0;
                                update_user(temp, 0);
                            }
                            else{
                                del_data(temp.username);
                            }
                            return;
                        }
                    }
                    else{
                        color("red");
                        printf("INVALID:\nThe given user doesn't exist\n");
                        color("reset");
                    }
                }
            }
            else{
                error_message(0);
            }
        }
        else{
            error_message(0);
        }
    }
}

void edit(){
    char input[ARRAY_SIZE];
    int check;
    while(1){
        printf("Enter '/back' to go back\n");
        printf("[1]Edit Topic\n[2]Edit Q&A\n");
        gets(input);
        system("cls");
        if(strcmp(input, "/back") == 0){
            return;
        }
        if(strlen(input) == 1){
            check = atoi(input);
            if(check >= 1 && check <= 2){
                if(check == 1){
                    while(1){
                        printf("Enter '/back' to go back\n");
                        printf("Enter '/editor' to go back to editor\n");
                        printf("[1]Add\n[2]Remove\n[3]Import\n");
                        gets(input);
                        system("cls");  
                        if(strcmp(input, "/back") == 0){
                            break;
                        }
                        else if(strcmp(input, "/editor") == 0){
                            return;
                        }
                        else{
                            check = atoi(input);
                            if(check >= 1 && check <= 3){
                                if(check == 1){
                                    if(editTopicCreate() == -2){
                                        return;
                                    }
                                }
                                else if(check == 2){
                                    if(editTopicRemove() == -2){
                                        return;
                                    }
                                }
                                else if(check == 3){
                                    if(editTopicImport() == -2){
                                        return;
                                    }
                                }
                            }
                            else{
                                error_message(0);
                            }
                        }
                    }
                }
                else if(check == 2){
                    char topic[47];
                    while(1){
                        check = askTopic(0);
                        if(check == -1){
                            break;
                        }
                        else if(check == 0){
                            error_message(0);
                        }
                        else{
                            getTopic(check, topic,0); // load topic name to string
                            while(1){
                                printf("Enter '/back' to go back\n");
                                printf("Enter '/editor' to go back to editor\n");
                                printf("[1]Add\n[2]Remove\n");
                                gets(input);
                                system("cls");  
                                if(strcmp(input, "/back") == 0){
                                    break;
                                }
                                else if(strcmp(input, "/editor") == 0){
                                    return;
                                }
                                else{
                                    check = atoi(input);
                                    if(check >= 1 && check <= 2){
                                        if(check == 1){
                                            if(editQA_add(topic) == -2){
                                                return;
                                            }
                                        }
                                        else if(check == 2){
                                            if(editQA_remove(topic) == -2){
                                                return;
                                            }
                                        }
                                    }
                                    else{
                                        error_message(0);
                                    }
                                }
                            }
                        }
                    } 
                }
            }
            else{
                error_message(0);
            }
        }
        else{
            error_message(0);
        }
    }
}