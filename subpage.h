#include "rlg.h"
#include "qaManager.h"

// MENU



/*
    1.Display all topic
    2.Ask user which topic to play
    3.Show amount of question
    4. Ask how many question will be ask
    5.Display playable mode
    6.Ask user which mode
*/

int askTopic(int mode){
    char input[ARRAY_SIZE];
    int choice, check;
    printf("Topic:\n");
    dis_all_topic(&choice,mode);
    printf("Enter '/back' to go back\n");
    if(choice == 0){
        system("cls");
        color("red");
        printf("There is no topic available yet.\n");
        printf("Try adding it in the editor mode\n");
        color("reset");
        return -1;
    }
    printf("Select: ");
    gets(input);
    system("cls");
    if (strcmp(input, "/back") == 0){
        return -1;
    }
    check = atoi(input);
    if (check <= choice && check >= 1){
        return check;
    }
    else{
        return 0;
    }
}

int askAmountQ(char topicChoose[], int *qa_Amount){
    char input[ARRAY_SIZE];
    int choice, check;
    printf("Topic: %s", topicChoose);
    printf("Amount: %d Questions\n", *qa_Amount);
    printf("Enter '/back' to go back\n");
    printf("Which amount do you prefer?\n");
    printf("[1]Standard\n[2]All\n[3]Others\n");
    gets(input);
    system("cls");
    if (strcmp(input, "/back") == 0){
        return -1;
    }
    else{
        check = atoi(input);
        if(check >= 1 && check <= 3){
            if(check == 1){
                *qa_Amount = stdq(*qa_Amount);
                return 1;             
            }
            else if(check == 2){
                return 1;
            }
            else if(check == 3){
                while (1){
                    printf("Topic: %s", topicChoose);
                    printf("Amount: %d Questions\n", *qa_Amount);
                    printf("Enter '/back' to go back\n");
                    printf("Selected: ");
                    gets(input);
                    system("cls");
                    if (strcmp(input, "/back") == 0){
                        break;
                    }
                    else{
                        check = atoi(input);
                        if(check >= 4 && check <= *qa_Amount){
                            *qa_Amount = check;
                            return 1;
                        }
                        else{
                            color("red");
                            printf("Please enter the numbers within range\n");
                            color("reset");
                        }
                    }
                    
                }
                                
            }
            
        }
        else{
            error_message(0);
            return 0;
        }
    }

}

int askMode(int *mode_Select){
    char input[ARRAY_SIZE];
    printf("Gamemode:\n");
    printf("[1]Quiz Game\n[2]Type it out\n[3]Blink of an eye\n");
    printf("Enter '/back' to go back\n");
    printf("Select: ");
    gets(input);
    system("cls");
    if(strcmp(input, "/back") == 0){
        return -1;
    }
    else{
        *mode_Select = atoi(input);
        if(*mode_Select >= 1 && *mode_Select <= 3){
            return 1;
        }
        else{
            error_message(0);
            return 0;
        }
    }
}

void quizGame(char *topic, int amount_Q, struct User *player, int mode){
    // Mode = 0 quizgame
    // Mode = 1 blink of an eye
    int pool_Q[amount_Q], pool_A[4];
    int max_Q = countQ(topic), check, cor = 0, incor = 0;
    char display[ARRAY_SIZE], input[ARRAY_SIZE];
    color("yellow");
    printf("Mode: Quiz Game\n");
    color("cyan");  
    printf("Topic: %s", topic);
    printf("Amount Q: %d\n", amount_Q);
    color("green");
    printf("Player name: %s\n", player->username);
    color("reset");
    system("pause");
    system("cls");
    fill_array_random_num(pool_Q, amount_Q, max_Q);
    for(int num = 0; num < amount_Q; num++){
        // set up for each Q
        get_Q(topic, pool_Q[num], display);
        fill_array_random_num(pool_A, 4, amount_Q); // random pool answer
        if(check_value_match_arr(pool_Q[num], pool_A, 4) == 0){ // check if ans already exist in the pool
            int random_inject = rand() % 4;
            pool_A[random_inject] = pool_Q[num]; // inject ans to pool answer 
        }
        // Displaying
        while(1){
            printf("%d. %s\n", num+1, display);
            for(int ans = 0; ans < 4 ; ans++){
                get_A(topic, pool_A[ans], display);
                if(ans%2 == 0){
                    printf("%c. %s\t\t", ans+65, display);
                }
                else{
                    printf("%c. %s\n", ans+65, display);
                }
            }
            if(mode == 1){
                delay(1);
                system("cls");
            }
            printf("Answer: ");
            gets(input);
            system("cls");
            if(strlen(input) == 1){
                check = input[0] - 65;
                if(check >= 0 && check <= 3){
                    break;
                }
                else{
                    error_message(0);
                }
            }
            else{
                error_message(0);
            }
        }
        // add info
        player->allq++;
        // Check if answer is correct
        if(pool_A[check] == pool_Q[num]){
            player->correctq++;
            if(mode == 1)
                player->score += 2.5;
            cor++;
        }
        else{
            player->wrongq++;
            incor++;
        }
    }
    update_user(*player, 0);
    color("yellow");
    printf("AllQ: %d\n",amount_Q);
    color("green");
    printf("Correct: %d\n", cor);
    color("red");
    printf("Incorrect: %d\n", incor);
    color("reset");
    system("pause");
    system("cls");
}

void type_it_out(char *topic, int amount_Q, struct User *player){
    int pool_Q[amount_Q];
    int max_Q = countQ(topic), cor = 0, incor = 0;
    char display[ARRAY_SIZE], input[ARRAY_SIZE];
    color("yellow");
    printf("Mode: Type it out\n");
    color("cyan");  
    printf("Topic: %s", topic);
    printf("Amount Q: %d\n", amount_Q);
    color("green");
    printf("Player name: %s\n", player->username);
    color("reset");
    system("pause");
    system("cls");
    fill_array_random_num(pool_Q, amount_Q, max_Q);
    for(int num = 0; num < amount_Q; num++){
        // set up for each Q
        get_Q(topic, pool_Q[num], display);
        // Displaying
        printf("%d. %s\n", num+1, display);
        printf("Answer: ");
        gets(input);
        system("cls");
        get_A(topic, pool_Q[num], display);
        player->allq++;
        if(strcmp(display, input)== 0){
            player->correctq++;
            player->score += 4;
            cor++;
        }
        else{
            player->wrongq++;
            incor++;
        }
    }
    update_user(*player, 0);
    color("yellow");
    printf("AllQ: %d\n",amount_Q);
    color("green");
    printf("Correct: %d\n", cor);
    color("red");
    printf("Incorrect: %d\n", incor);
    color("reset");
    system("pause");
    system("cls");
}

int admin_confirmation(){
    char password[ARRAY_SIZE];
    while(1){
        printf("Enter '/back' to go back\n");
        color("red");
        printf("Admin Password: ");
        get_pass(password);
        system("cls");
        if(strcmp(password, "/back") == 0){
            color("reset");
            return -1;
        }
        if(check_match("root", password) == 1){
            color("reset");
            return 1;
        }
        else{
            printf("Incorrect Password\n");
            color("reset");
        }
        
    }
}

int editTopicCreate(){
    char input[ARRAY_SIZE];
    while(1){
        dis_all_topic(NULL , 0);
        printf("\nEnter '/back' to go back\n");
        printf("Enter '/editor' to go back to editor\n");
        printf("Topic name must be in range 1 - 47\n");
        printf("Topic Name: ");
        gets(input);
        system("cls");
        if(strcmp(input, "/back") == 0){
            return -1;
        }
        else if(strcmp(input, "/editor") == 0){
            return-2;
        }

        if(checkTopicSyntax(input)==1){
            if(check_topic_exist(input) == 0){
                create_topic(input);
                color("green");
                printf("Sucessfully Created\n");
                color("reset");
            }
            else{
                color("red");
                printf("Topic already exist\n");
                color("reset");
            }
        }
        else{
            color("red");
            printf("Invalid Length\n");
            color("reset");
        }
    }
}



int editTopicRemove(){
    char input[ARRAY_SIZE];
    int maxTopic, check;
    while(1){
        dis_all_topic(&maxTopic, 0);
        printf("\nEnter '/back' to go back\n");
        printf("Enter '/editor' to go back to editor\n");
        printf("Topic Number: ");
        gets(input);
        system("cls");
        if(strcmp(input, "/back") == 0){
            return -1;
        }
        else if(strcmp(input, "/editor") == 0){
            return-2;
        }
        check = atoi(input);
        if(check >= 1 && check <= maxTopic){
            delete_topic(check);
            color("green");
            printf("Sucessfully deleted\n");
            color("reset");
        }
        else{
            error_message(0);
        }
    }
}

int editTopicImport(){
    char input[ARRAY_SIZE], name[47];
    int maxTopic, check;
    while(1){
        printf("Enter '/back' to go back\n");
        printf("Enter '/editor' to go back to editor\n\n");
        printf("Syntax:\t1.The last paragrah must be empty\n\t2.Question and Answer amount must match\n");
        printf("\nExample:1. C:\\\\Users\\\\some\\\\Desktop\\\\test.txt\n");
        printf("\t2. C:/Users/some/Desktop/test.txt\n");
        printf("File path: ");
        gets(input);
        system("cls");
        if(strcmp(input, "/back") == 0){
            return -1;
        }
        else if(strcmp(input, "/editor") == 0){
            return-2;
        }
        else{
            check = checkfile(input);
            if(check == 1){
                while(1){
                    printf("Enter '/back' to go back\n");
                    printf("Enter '/editor' to go back to editor\n");
                    printf("Topic Name: ");
                    gets(name);
                    system("cls");
                    if(strcmp(name, "/back") == 0){
                        break;
                    }
                    else if(strcmp(name, "/editor") == 0){
                        return-2;
                    }
                    else{
                        if(checkTopicSyntax(name) == 1){
                            if(check_topic_exist(name) == 0){
                                create_topic(name);
                                copyfile(input, name);
                                color("green");
                                printf("Sucessfully import a new file\n");
                                color("reset");
                                return 1;
                            }
                            else{
                                color("red");
                                printf("The name is already taken\n");
                                color("reset");
                            }
                        }
                        else{
                            color("red");
                            printf("Your Topic name should be under 47 characters\n");
                            color("reset");
                        }
                    }
                }
            }
            else if(check == 0){
                color("red");
                printf("File not found\n");
                color("reset");
            }
            else if(check == -1){
                color("red");
                printf("The last paragrah is not empty\n");
                color("reset");
            }
            else if(check == -1){
                color("red");
                printf("Questions and Answers not match\n");
                color("reset");
            }
        }
        
    }
}

int editQA_add(char chosenTopic[]){
    char question[ARRAY_SIZE], answer[ARRAY_SIZE];
    while(1){
        dis_all_QandA(chosenTopic, NULL);
        printf("\nEnter '/back' to go back\n");
        printf("Enter '/editor' to go back to editor\n");
        printf("Question: ");
        gets(question);
        system("cls");
        if(strcmp(question, "/back") == 0){
            return -1;
        }
        else if(strcmp(question, "/editor") == 0){
            return -2;
        }
        else{
            while (1)
            {
                dis_all_QandA(chosenTopic, NULL);
                printf("\nEnter '/back' to go back\n");
                printf("Enter '/editor' to go back to editor\n");
                printf("Question: %s\n", question);
                printf("Answer: ");
                gets(answer);
                system("cls");
                system("cls");
                if(strcmp(answer, "/back") == 0){
                    break;
                }
                else if(strcmp(answer, "/editor") == 0){
                    return -2;
                }
                else{
                    add_QandA(chosenTopic, question, answer);
                    break;
                }
            }
            
        }
    }
    
}

int editQA_remove(char chosenTopic[]){
    char input[ARRAY_SIZE];
    int maxQ;
    int check;
    while(1){
        dis_all_QandA(chosenTopic, &maxQ);
        printf("\nEnter '/back' to go back\n");
        printf("Enter '/editor' to go back to editor\n");
        printf("Remove Question Num: ");
        gets(input);
        system("cls");
        if(strcmp(input, "/back") == 0){
            break;
        }
        else if(strcmp(input, "/editor") == 0){
            return -2;
        }
        else{
            check = atoi(input);
            if(check >= 1 && check <= maxQ){
                delete_QandA(check, chosenTopic);
            }
        }
    }
}