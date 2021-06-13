/*
ID: 63011293
Name: Raviphas Sananpanichkul
Midterm Project
C PROGRAMMING
Teacher: Ukrit Watchareeruetai
University: King Mongkut's Institute of Technology Ladkrabang
*/


void guest() {
    strcpy(currentuser.username, "TEMP GUEST");
    currentuser.wq, currentuser.cq = 0, 0;
    currentuser.allq, currentuser.score = 0, 0;
}
int change_ps(char username[], char password[], double score, double allq, int cq, int wq) {
    char passw[100];
    while (1)
    {
        printf("Enter '/menu' to go back to the menu.\n");
        printf("Please enter the current password: ");
        get_pass(temp);
        if (strcmp(temp, "/menu") == 0)
            return 1;
        else if (strcmp(temp, password) == 0) { // user confirm successful
            if (take_password_reg(passw) == 1)
                break;
        }
        system("cls");
    }
    update_user(username, passw, score, allq, cq, wq);
    strcpy(password, passw);
    printf("\033[0;32mSucessfully change password\033[0m\n");
    delay(1);
    return 1;
}
void dis_user_info() {
    struct usinfo temp;
    system("cls");
    while (1)
    {
        if (take_username_log(temp.username) == -1)
            return; //user wants to go back to the menu
        else
            break;
    }
    load_score_temp(temp.username);
    printf("Rank: %d\n", get_rank(temp.username));
    printf("Username: %s\n", temp.username);
    printf("Total_score: %02.2lf\n", tempuser.score);
    printf("All Q: %.0lf\n", tempuser.allq);
    printf("\033[0;32mCorrect Q: %d\033[0m\n", tempuser.cq);
    printf("\033[1;31mWrong Q: %d\033[0m\n", tempuser.wq);
    if (tempuser.allq == 0) {
        printf("Percent Correct: %02.2lf %%\n", 0);
    }
    else
        printf("Correct Percentage: %02.2lf %%\n", (tempuser.cq / tempuser.allq) * 100);
    system("pause");
    system("cls");
}

//gamemode
void quiz(char topic[], int am_q, int* p_q) {
    int cor_q = 0, wro_q = 0;
    int ans_ar[4];
    char question[500], answer[500];
    for (int index_Q = 0; index_Q < am_q; index_Q++)
    {
        int numoftheQ = p_q[index_Q];
        fill_array_random_num(ans_ar, 4, am_q);// random pool ans
        if (valueinarray(numoftheQ, ans_ar, 4) == 0)
            ans_ar[rand() % 4] = numoftheQ;//Inject the answer to the array
        get_Q(topic, numoftheQ, question);
        while (1) {
            printf("%d.%s\n", index_Q + 1, question);//display question
            for (int index_ans = 0; index_ans < 4; index_ans++)// display all choice
            {
                get_A(topic, ans_ar[index_ans], answer);
                printf("(%d)%s\n", index_ans + 1, answer);
            }
            scanf("%s", choice);
            if (strlen(choice) == 1) {
                if (atoi(choice) >= 1 && atoi(choice) <= 4)
                    break;
            }
            else
                system("cls");
        }
        if (atoi(choice) == findvalinarr(ans_ar, 4, numoftheQ))
            cor_q++;
        else
            wro_q++;
        system("cls");
    }
    printf("You've answered:\n");
    printf("\033[0;32mCorrect: %d\t", cor_q);
    printf("\033[0;31mIncorrect: %d\033[0m\n", wro_q);
    printf("Total: %d questions\n", am_q);
    double ad_score = (am_q + cor_q - wro_q) / 2.0;
    printf("Score added: %.2lf\n", ad_score);
    double dam_q = (double)am_q;
    currentuser.score += ad_score;
    currentuser.allq += dam_q;
    currentuser.cq += cor_q;
    currentuser.wq += wro_q;
    system("pause");
    update_user(currentuser.username, currentuser.password, currentuser.score, currentuser.allq, currentuser.cq, currentuser.wq);
    system("cls");
    while (1) {
        printf("Do you want to see all the correct ans?\n");
        printf("(1)Yes or (2)No\n");
        scanf("%s", choice);
        system("cls");
        if (strlen(choice) == 1)
            if (atoi(choice) == 1 || atoi(choice) == 2);
        break;
    }
    if (atoi(choice) == 1)
        dis_all_QandA(topic, am_q, p_q);
    free(p_q);
}
void timeattack(char topic[], int am_q, int* p_q) {
    int cor_q = 0, wro_q = 0, tm_out = 0;
    int ans_ar[4];
    char question[500], answer[500];
    time_t start;
    time_t stop;
    for (int index_Q = 0; index_Q < am_q; index_Q++)
    {
        int numoftheQ = p_q[index_Q];
        fill_array_random_num(ans_ar, 4, am_q);// random pool ans
        if (valueinarray(numoftheQ, ans_ar, 4) == 0)
            ans_ar[rand() % 4] = numoftheQ;//Inject the answer to the array
        get_Q(topic, numoftheQ, question);
        printf("%d.%s\n", index_Q + 1, question);//display question
        for (int index_ans = 0; index_ans < 4; index_ans++)// display all choice
        {
            get_A(topic, ans_ar[index_ans], answer);
            printf("(%d)%s\n", index_ans + 1, answer);
        }
        double diff = 0.0;
        time(&start);
        scanf("%s", choice);
        time(&stop);
        system("cls");
        diff = difftime(stop, start);
        if (strlen(choice) != 1)
            wro_q++;
        else if (atoi(choice) < 1 && atoi(choice) > 4)
            wro_q++;
        else {
            if (atoi(choice) == findvalinarr(ans_ar, 4, numoftheQ) && diff <= 3)
                cor_q++;
            else
                tm_out++;
        }
        system("cls");
    }
    printf("You've answered:\n");
    printf("\033[0;32mCorrect: %d\t", cor_q);
    printf("\033[0;31mIncorrect: %d\t", wro_q);
    printf("\033[0;31mTime out: %d\033[0m\n", tm_out);
    printf("Total: %d questions\n", am_q);
    double ad_score = (am_q + cor_q - wro_q - tm_out) * 0.75;
    printf("Score added: %.2lf\n", ad_score);
    double dam_q = (double)am_q;
    currentuser.score += ad_score;
    currentuser.allq += dam_q;
    currentuser.cq += cor_q;
    currentuser.wq += wro_q;
    system("pause");
    update_user(currentuser.username, currentuser.password, currentuser.score, currentuser.allq, currentuser.cq, currentuser.wq);
    system("cls");
    while (1) {
        printf("Do you want to see all the correct ans?\n");
        printf("(1)Yes or (2)No\n");
        scanf("%s", choice);
        system("cls");
        if (strlen(choice) == 1)
            if (atoi(choice) == 1 || atoi(choice) == 2);
        break;
    }
    if (atoi(choice) == 1)
        dis_all_QandA(topic, am_q, p_q);
    free(p_q);
}
void typeitout(char topic[], int am_q, int* p_q) {
    int cor_q = 0, wro_q = 0;
    char question[500], answer[500];
    char usin;
    if (am_q > 10)
        am_q = 10;
    for (int index_Q = 0; index_Q < am_q; index_Q++)
    {
        int numoftheQ = p_q[index_Q];
        get_Q(topic, numoftheQ, question);
        printf("%d.%s\n", index_Q + 1, question);//display question
        get_A(topic, numoftheQ, answer);
        printf("%s\n", answer);
        int count = 0;
        printf("\033[0;32m");
        while (count != strlen(answer))
        {
            usin = getch();
            if (usin == answer[count]) {

                printf("%c", usin);
                count++;
            }
        }
        printf("\033[0m");
        system("cls");
    }
    printf("The End\nGood job :)\n\033[0m\n");
    delay(1);
    free(p_q);
}
void blinkofaneye(char topic[], int am_q, int* p_q) {
    int cor_q = 0, wro_q = 0;
    int ans_ar[4];
    char question[500], answer[500];
    for (int index_Q = 0; index_Q < am_q; index_Q++)
    {
        int numoftheQ = p_q[index_Q];
        fill_array_random_num(ans_ar, 4, am_q);// random pool ans
        if (valueinarray(numoftheQ, ans_ar, 4) == 0)
            ans_ar[rand() % 4] = numoftheQ;//Inject the answer to the array
        get_Q(topic, numoftheQ, question);
        printf("%d.%s\n", index_Q + 1, question);//display question
        for (int index_ans = 0; index_ans < 4; index_ans++)// display all choice
        {
            get_A(topic, ans_ar[index_ans], answer);
            printf("(%d)%s\n", index_ans + 1, answer);
        }
        delay(2);
        system("cls");
        while (1) {
            printf("What is the answer?");
            scanf("%s", choice);
            system("cls");
            if (strlen(choice) == 1)
                if (atoi(choice) >= 1 && atoi(choice) <= 4)
                    break;
        }
        if (atoi(choice) == findvalinarr(ans_ar, 4, numoftheQ))
            cor_q++;
        else
            wro_q++;
        system("cls");
    }
    printf("You've answered:\n");
    printf("\033[0;32mCorrect: %d\t", cor_q);
    printf("\033[0;31mIncorrect: %d\n", wro_q);
    reset_color();
    printf("Total: %d questions\n", am_q);
    double ad_score = (am_q + cor_q - wro_q);
    printf("Score added: %.2lf\n", ad_score);
    double dam_q = (double)am_q;
    currentuser.score += ad_score;
    currentuser.allq += dam_q;
    currentuser.cq += cor_q;
    currentuser.wq += wro_q;
    system("pause");
    update_user(currentuser.username, currentuser.password, currentuser.score, currentuser.allq, currentuser.cq, currentuser.wq);
    system("cls");
    while (1) {
        printf("Do you want to see all the correct ans?\n");
        printf("(1)Yes or (2)No\n");
        scanf("%s", choice);
        system("cls");
        if (strlen(choice) == 1)
            if (atoi(choice) == 1 || atoi(choice) == 2);
        break;
    }
    if (atoi(choice) == 1)
        dis_all_QandA(topic, am_q, p_q);
    free(p_q);
}

//big func
int rlg() {
    while (1)
    {
        printf("Enter '/quit' to quit.\n");
        printf("(1)Register\n(2)Login\n(3)Guest\n");
        gets(choice);
        system("cls");
        if (strcmp(choice, "/quit") == 0)
            end_message();
        if (strlen(choice) == 1)
            if (atoi(choice) >= 0 && atoi(choice) <= 3) {
                int check = atoi(choice);
                if (check == 1) {
                    if (regis() == 1)
                        break;
                }
                else if (check == 2) {
                    if (login() == 1)
                        break;
                }
                else if (check == 3) {
                    guest();
                    break;
                }
                system("cls");
            }
    }
    if (strcmp(currentuser.username, admin.username) == 0 && strcmp(currentuser.password, admin.password) == 0) {
        system("cls");
        printf("\033[0;36mWelcome to the editor mode\033[0m\n");
        system("pause");
        system("cls");
        return 1;
    }
    else { // if it is not admin
        welcome();
        return 0;
    }
}
int play() {
    char topic[100];
    int size_t;
    FILE* filepointer;
    while (1) { // big loop for catching back before game plays
        filepointer = fopen("topic.txt", "r");
        while (1) {
            size_t = 1;
            printf("All available topics:\n");
            char read[100];
            while (fgets(read, 100, filepointer) != NULL) { //display all topic available
                strcpy(temp, read);
                change_topictofile(temp);
                int check_Q = countQ(temp);
                if (check_QandA(temp) == 0 && check_Q >= 4 && check_Q < 1000) { //only topic that have at least 4 Questions and does not violate syntax
                    printf("%d. %s", size_t, read);// will be print
                    size_t++;
                }
            }
            fseek(filepointer, 0, SEEK_SET);
            if (size_t == 1) {// there is no topic file that is available
                printf("\033[0;31mSorry, but there is no topic available yet so we will redirecting you back to the menu.\033[0m\n");
                delay(2);
                system("cls");
                fclose(filepointer);
                return -1;
            }
            // to ask what topic user prefer
            printf("Please enter the number of the topic that will be played.\n");
            printf("If you want to return to the menu, enter '/menu'\n");
            scanf("%s", choice);
            system("cls");
            if (strcmp(choice, "/menu") == 0) //user want to go to menu
                return -1;
            else if (strlen(choice) == 1)
                if (atoi(choice) >= 1 && atoi(choice) < size_t)
                    break;
        }
        int count = 1;
        fseek(filepointer, 0, SEEK_SET);
        while (fgets(read, array_length, filepointer) != NULL) //find the selected topic named
        {
            if (count == atoi(choice)) {
                strcpy(topic, read);
            }
            count++;
        }
        fclose(filepointer);
        change_topictofile(topic);
        while (1) {
            printf("Which amount do you prefer?\n");
            printf("If you want to go back, enter '/back'\n");
            printf("(1)Normal\n(2)Quick Revision\n(3)All\n");
            scanf("%s", choice);
            system("cls");
            if (strcmp(choice, "/back") == 0) //user want to go to selecting the topic
                break;
            if (strlen(choice) == 1)
                if (atoi(choice) >= 1 && atoi(choice) <= 3) {
                    int am_q = countQ(topic);
                    if (atoi(choice) == 1)
                        am_q = stdq(topic);
                    else if (atoi(choice) == 2) {
                        if (am_q >= 10)
                            am_q = stdq(topic) / 2;
                        else
                            am_q = stdq(topic);
                    }
                    else
                        am_q = countQ(topic);
                    while (1) {
                        printf("Which gamemode?\n");
                        printf("If you want to go back, enter '/back'\n");
                        printf("(1)Normal Quiz Game\n(2)Time attack\n(3)Type it out!(No Rank)\n(4)Blink of an eye\n");
                        scanf("%s", choice);
                        system("cls");
                        if (strcmp(choice, "/back") == 0) //user want to go to menu
                            break;
                        if (strlen(choice) == 1) {
                            if (atoi(choice) >= 1 && atoi(choice) <= 4) {
                                int* p_q = (int*)malloc(am_q * sizeof(int));
                                fill_array_random_num(p_q, am_q, am_q);
                                if (atoi(choice) == 1) {
                                    quiz(topic, am_q, p_q);\
                                        return 1;
                                }
                                else if (atoi(choice) == 2) {
                                    timeattack(topic, am_q, p_q);
                                    return 1;
                                }
                                else if (atoi(choice) == 3) {
                                    typeitout(topic, am_q, p_q);
                                    return 1;
                                }
                                else if (atoi(choice) == 4) {
                                    blinkofaneye(topic, am_q, p_q);
                                    return 1;
                                }
                            }

                        }
                    }

                }
        }
        if (strcmp(choice, "/back") == 0) //user want to go to selecting the topic
            system("cls");
    }
}

//menu
void menu() {
    while (1)
    {
        int usin = user_choice("MENU\n(1)Play\n(2)Guide\n(3)User Info\n(4)Leader board\n(5)Change account\n(6)Change password\n(7)Exit\n", 1, 7);
        if (usin == 1)
            play();
        else if (usin == 2)
            guide();
        else if (usin == 3)
            dis_user_info();
        else if (usin == 4)
            disleaderboard();
        else if (usin == 5 || usin == -1)
            rlg();
        else if (usin == 6) {
            if (strcmp("TEMP GUEST", currentuser.username) == 0) {
                printf("\033[0;31mSorry, but you're a guest you can't change any password.\033[0m\n");
                delay(1);
            }
            else
                change_ps(currentuser.username, currentuser.password, currentuser.score, currentuser.allq, currentuser.cq, currentuser.wq);
        }
        else if (usin == 7)
            end_message();
        if (strcmp(admin.username, currentuser.username) == 0)
            break;
        system("cls");
    }

}

//editor func
int dis_all_top() {
    FILE* filepointer;
    printf("All available topics:\n");
    int count = 1;
    filepointer = fopen("topic.txt", "r");
    if (filepointer == NULL) {
        red();
        printf("There is no database to be found yet.\n");
        reset_color();
        system("pause");
        system("cls");
        return -1;
    }
    else {
        char read[100];
        while (fgets(read, 100, filepointer) != NULL) { //display all topic available
            printf("%d. %s", count, read);
            count++;
        }
        fclose(filepointer);
    }
    return count;
}
void delete_topic(int num_del) {
    FILE* fp, * fpdel;
    char del_name[array_length];
    int count = 1;
    fpdel = fopen("temp_top_del.txt", "w");
    fp = fopen("topic.txt", "r");
    char read[array_length];
    while (fgets(read, array_length, fp) != NULL) {
        if (count != num_del) {
            fprintf(fpdel, "%s", read);
        }
        else if (count == num_del) {
            strcpy(del_name, read);
        }
        count++;
    }
    fclose(fp);
    fclose(fpdel);
    remove("topic.txt");
    rename("temp_top_del.txt", "topic.txt");
    change_topictofile(del_name);
    remove(del_name);
}
int create_topic() {
    system("cls");
    FILE* fp;
    char topname[array_length];
    while (1) {
        printf("Enter '/back' to go back.\n");
        printf("The topic shouldn't be longer than 99 charaters.\n");
        printf("The topic shouldn't contain any special characters.\n");
        printf("Topic's name: ");
        gets(topname);
        if (strcmp(temp, "/back") == 0)
            return -1;
        else if (check_topic_exist(topname) == 1)
        {
            system("cls");
            printf("\033[0;31mSorry, but this topic is already taken.\033[0m\n");
        }
        else if (check_if_sp(topname) == 1) {
            system("cls");
            printf("\033[0;31mSorry, but this name is in valid.\033[0m\n");
        }
        else
        {
            system("cls");
            break;
        }
    }
    fp = fopen("topic.txt", "a");
    fprintf(fp, "%s\n", topname);
    fclose(fp);
    change_topictofile(topname);
    fp = fopen(topname, "w");
    fclose(fp);
    return 1;
}
void clear_score() {
    if (user_choice("Are you sure you want to clear all user's score?\n(1)Yes or (2)No\n", 1, 2) == 1) {
        FILE* fTemp, * filepointer;
        fTemp = fopen("temp_clear.csv", "w");
        filepointer = fopen("userdata.csv", "r");
        char* token;
        while (fgets(read, array_length, filepointer) != NULL)
        {
            token = strtok(read, ",");
            fprintf(fTemp, "%s,", token);
            token = strtok(NULL, ",");
            fprintf(fTemp, "%s,", token);
            fprintf(fTemp, "0,0,0,0\n");
        }
        fclose(filepointer);
        fclose(fTemp);
        remove("userdata.csv");
        rename("temp_clear.csv", "userdata.csv");
        printf("\033[0;32mSuccesfully cleared the score\033[0m\n");
        delay(1);
    }
    else
        return;
}
int force_change_ps() {
    struct usinfo temp;
    while (1)
    {
        if (take_username_log(temp.username) == -1)
            return -1; //user wants to go back to the menu
        else {
            if (take_password_reg(temp.password) == 1)
                break;
            else //user wants to go change username
                system("cls");
        }

    }
    load_score_temp(temp.username);
    update_user(temp.username, temp.password, tempuser.score, tempuser.allq, tempuser.cq, tempuser.wq);
    printf("\033[0;32mSucessfully change password\033[0m\n");
    delay(1);
    return 1;
}
void get_user_pass(char user[], char rechar[]) {
    FILE* filepointer;
    filepointer = fopen("userdata.csv", "r");
    char* token;
    while (fgets(read, array_length, filepointer) != NULL)
    {
        token = strtok(read, ",");
        if (strcmp(user, token) == 0) {
            token = strtok(NULL, ",");
            strcpy(rechar, token);
            break;
        }
    }
    fclose(filepointer);
}
int edit_topic() {
    system("cls");
    while (1)
    {
        int count = dis_all_top();
        printf("\nEnter '/back' to go back.\n");
        printf("Enter '/menu' to go menu.\n");
        printf("Enter the number that is shown then the program will delete that topic.\n");
        printf("Enter the number that more than shown by 1 then the program will create a new topic.\n");
        printf("For example if there is 3 topics you need to enter 4 to create a new topic.\n");
        printf("If there is 0 topics then enter 1 to create a new topic.\n");
        gets(choice);
        system("cls");
        if (strcmp(choice, "/back") == 0)
            return -1;
        else if (strcmp(choice, "/menu") == 0)
            return -2;
        else
        {
            if (0 < atoi(choice) && atoi(choice) < count) {
                delete_topic(atoi(choice));
                system("cls");
                green();
                printf("Successfully delete the selected topic.\n");
                reset_color();
                delay(2);

            }
            else if (atoi(choice) == count || count == 1) {
                if (create_topic() == 1) {
                    system("cls");
                    green();
                    printf("Successfully created a new topic.\n");
                    reset_color();
                    delay(2);
                }
                else
                    system("cls");
            }

        }
        system("cls");
    }
    system("cls");
}
int create_QandA(char topic[]) {
    system("cls");
    FILE* filepointer;
    if (countQ(topic) >= 1000) {
        printf("The limit has been reached to add more question.");
        printf("\nIf you desire to add more question please consider delelte some question\n");
        printf("or create a new topic for it.\n");
        return 0;
    }
    else {
        system("cls");
        char question[550], answer[550];
        while (1)
        {
            while (1)
            {
                printf("Question must not be longer than 500 characters.\n");
                printf("The question must not include '|'\n");
                printf("To start a new line use '\\n'.\n");
                printf("Enter '/back' to go back.\n");
                printf("Enter '/menu' to go menu.\n");
                printf("Question: ");
                gets(question);
                system("cls");
                if (strcmp(question, "/back") == 0)
                    return -1;
                else if (strcmp(question, "/menu") == 0)
                    return -2;
                red();
                if (strlen(question) > 500)
                    printf("Error: You enter more than 500 characters!");
                if (check_ban(question) == 1)
                    printf("Error: You enter the ban character.\n");
                reset_color();
                if (strlen(question) <= 500 && check_ban(question) == 0)
                    break;
            }
            while (1)
            {
                printf("Answer must not be longer than 500 characters.\n");
                printf("The answer must not include '|'\n");
                printf("To start a new line use '\\n'.\n");
                printf("Enter '/back' to go back.\n");
                printf("Answer: ");
                gets(answer);
                system("cls");
                if (strcmp(answer, "/back") == 0)
                    break;
                red();
                if (strlen(answer) > 500)
                    printf("Error: You enter more than 500 characters!\n");
                if (check_ban(answer) == 1)
                    printf("Error: You enter the ban character.\n");
                reset_color();
                if (strlen(answer) <= 500 && check_ban(answer) == 0) {
                    printf("Q:");
                    disp_qanda(question);
                    printf("A:");
                    disp_qanda(answer);
                    printf("Confirm?\n");
                    int check = user_choice("(1)Yes or (2)No\n", 1, 2);
                    if (check == 0) {
                        system("cls");
                    }
                    else if (check == 1) {
                        filepointer = fopen(topic, "a");
                        fprintf(filepointer, "%s|%s\n", question, answer);
                        fclose(filepointer);
                        system("cls");
                        green();
                        printf("Succesfully added the question.\n");
                        reset_color();
                        delay(2);
                        return 1;
                    }
                }

            }
        }
    }
}
void delete_QandA(int num_del, char topic[]) {
    system("cls");
    FILE* fTemp, * filepointer;
    fTemp = fopen("temp_del.txt", "w");
    filepointer = fopen(topic, "r");
    int count = 1;
    while (fgets(read, array_length, filepointer) != NULL) {
        if (count != num_del) {
            fprintf(fTemp, "%s", read);
        }
        count++;
    }
    fclose(filepointer);
    fclose(fTemp);
}
int edit_QandA() {
    FILE* filepointer;
    char topic[array_length];
    system("cls");
    while (1) {
        int count = dis_all_top();
        int edit_num;
        printf("\nEnter '/back' to go back.\n");
        printf("Enter '/menu' to go menu.\n");
        printf("Enter the number of the topic that you want to edit.\n");
        gets(choice);
        system("cls");
        if (strcmp(choice, "/back") == 0)
            return -1;
        else if (strcmp(choice, "/menu") == 0)
            return -2;
        else
        {
            if (0 < atoi(choice) && atoi(choice) < count) { // ask user which topic to edit Q&A
                count = 1;
                filepointer = fopen("topic.txt", "r");
                char read[array_length];
                while (fgets(read, array_length, filepointer) != NULL) {
                    if (count == atoi(choice)) {
                        strcpy(topic, read);
                    }
                    count++;
                }
                fclose(filepointer);
                change_topictofile(topic);
                char* token;
                while (1)
                {
                    filepointer = fopen(topic, "r");
                    count = 1;
                    while (fgets(read, 1000, filepointer) != NULL) { // display all qanda
                        strcpy(temp, read);
                        if (strcmp(temp, "") != 0) {
                            printf("%d.\n", count);
                            token = strtok(temp, "|");
                            printf("Q:");
                            disp_qanda(token);
                            token = strtok(NULL, "\n");
                            printf("A:");
                            disp_qanda(token);
                            printf("\n");
                            count++;
                        }
                    }
                    printf("\nEnter '/back' to go back.\n");
                    printf("Enter the number that is shown then the program will delete that Q&A.\n");
                    printf("Enter the number that more than shown by 1 then the program will create a new Q&A.\n");
                    printf("For example if there is 3 Questions you need to enter 4 to create a new Q&A.\n");
                    printf("Another example if there is 0 Questions you need to enter 1 to create a new Q&A.\n");
                    gets(choice);
                    system("cls");
                    if (strcmp(choice, "/back") == 0) {
                        fclose(filepointer);
                        break;
                    }
                    if (0 < atoi(choice) && atoi(choice) <= count) {
                        edit_num = atoi(choice);
                        if (edit_num == count) {
                            if (create_QandA(topic) == -1)
                            {
                                fclose(filepointer);
                                system("cls");
                                break;
                            }
                            else
                                return 1;
                        }
                        else if (edit_num < count) {
                            delete_QandA(edit_num, topic);
                            fclose(filepointer);
                            remove(topic);
                            rename("temp_del.txt", topic);
                            green();
                            printf("Successfully deleted the question.\n");
                            reset_color();
                            delay(2);
                        }
                    }
                }
            }
            system("cls");
        }
    }
}
int load_topic() {
    FILE* filepointer;
    char filepath[array_length];
    while (1) {
        while (1) {
            printf("Enter '/back' to go back.\n");
            printf("If you want to return to the menu, enter '/menu'\n");
            printf("Example file path: C:\\Users\\Asus\\Desktop\\tempt.txt\n");
            printf("Example format: QUESTION|ANSWER\n");
            printf("File path: ");
            scanf("%s", filepath);
            if (strcmp(filepath, "/back") == 0)
                return -1;
            else if (strcmp(filepath, "/menu") == 0)
                return -2;
            FILE* fp = fopen(filepath, "r");
            if (fp == NULL) {
                system("cls");
                red();
                printf("Sorry but this file doesn't exist.\nPlease try again\n");
                reset_color();
            }
            else {
                fclose(fp);
                green();
                printf("File found!\n");
                reset_color();
                delay(1);
                break;
            }
        }
        int checkFile = check_QandA(filepath);
        if (countQ(filepath) >= 1000) {
            system("cls");
            red();
            printf("The file contains more than 999 questions.\nPlease delete some and try again.\n");
            reset_color();
        }
        else if (countQ(filepath) < 4) {
            system("cls");
            red();
            printf("The file contains at least 4 questions.\nPlease add some and try again.\n");
            reset_color();
        }
        else if (checkFile != 0) {
            system("cls");
            red();
            printf("The file contains an invalid Q&A.\nPlease check Q number %d\n", checkFile);
            printf("It should contain only one '|'.\n");
            reset_color();
        }
        else {
            system("cls");
            char topname[100];
            green();
            printf("File passed from checking\n");
            reset_color();
            delay(1);
            system("cls");
            while (1)
            {
                printf("Enter '/back' to go back.\n");
                printf("New topic's name: ");
                scanf("%s", topname);
                system("cls");
                if (strcmp(topname, "/back") == 0) {
                    system("cls");
                    break;
                }

                else if (check_topic_exist(topname) == 1) {
                    system("cls");
                    red();
                    printf("Sorry, but this topic is already taken.\n");
                    reset_color();
                }
                else {
                    filepointer = fopen("topic.txt", "a");
                    fprintf(filepointer, "%s\n", topname);
                    fclose(filepointer);
                    change_topictofile(topname);
                    FILE* fp = fopen(filepath, "r");
                    filepointer = fopen(topname, "w");
                    while (fgets(read, array_length, fp) != NULL) {
                        if (strcmp(read, "\n") != 0) {
                            fprintf(filepointer, "%s", read);
                        }
                    }
                    fclose(filepointer);
                    fclose(fp);
                    green();
                    printf("Successfully loaded a topic\n");
                    reset_color();
                    delay(1);
                    return 1;
                }
            }

        }

    }

}
int edit() {
    int process;
    while (1)
    {
        system("cls");
        printf("If you want to return to the menu, enter '/menu'\n");
        printf("(1)Edit topic\n(2)Edit QandA\n(3)Load a topic\n");
        gets(choice);
        if (strcmp(choice, "/menu") == 0)
        {
            return -1;
        }
        if (strlen(choice) == 1)
        {
            int check = atoi(choice);
            if (check >= 1 && check <= 3) {
                if (check == 1) {
                    process = edit_topic();
                    if (process == -1)
                    {
                        system("cls");
                    }
                    else if (process == -2 || process == 1) {
                        system("cls");
                        return 1;
                    }
                }
                else if (check == 2) {
                    process = edit_QandA();
                    if (process == -1)
                    {
                        system("cls");
                    }
                    else if (process == -2 || process == 1) {
                        system("cls");
                        return 1;
                    }
                }
                else if (check == 3) {
                    system("cls");
                    process = load_topic();
                    if (process == -1)
                    {
                        system("cls");
                    }
                    else if (process == -2 || process == 1) {
                        system("cls");
                        return 1;
                    }
                }
            }
        }
        system("cls");
    }
}
void clear_data() {
    if (user_choice("Clear all data?\n*Warning all data will be delted permenantly*\n(1)Yes or (2)No\n", 1, 2) == 1) {
        FILE* clearfp;
        clearfp = fopen("topic.txt", "r");
        while (fgets(read, 100, clearfp) != NULL) {
            change_topictofile(read);
            remove(read);
        }
        clearfp = fopen("topic.txt", "w");
        fprintf(clearfp, "");
        clearfp = fopen("userdata.csv", "w");
        fprintf(clearfp, "");
        fclose(clearfp);
        green();
        printf("Successfully clear all data.\n");
        reset_color();
    }
}
void load_admin() {
    FILE* fp = fopen("admin.txt", "r");
    char* token;
    fgets(read, 100, fp);
    token = strtok(read, "|");
    strcpy(admin.username, token);
    token = strtok(NULL, "\n");
    strcpy(admin.password, token);
    fclose(fp);
}
int change_admin_name() {
    char usin[100];
    printf("If you want to go back enter '/back'\n");
    printf("New admin's name: ");
    gets(usin);
    system("cls");
    if (strcmp(usin, "/back") == 0)
        return -1;
    else {
        strcpy(admin.username, usin);
        strcpy(currentuser.username, usin);
        FILE* fp = fopen("admin.txt", "w");
        fprintf(fp, "%s|%s", admin.username, admin.password);
        fclose(fp);
        return 1;
    }
}
int change_admin_pass() {
    char usin[100];
    if (take_password_reg(usin) == -1)
        return -1;
    else {
        strcpy(admin.password, usin);
        strcpy(currentuser.password, usin);
        FILE* fpc = fopen("admin.txt", "w");
        fprintf(fpc, "%s|%s", admin.username, admin.password);
        fclose(fpc);
        return 1;
    }
}

//editor main menu
void editor() {
    while (1) {
        int usin = user_choice("\033[0;36mEDITOR\033[0m\n(1)Edit\n(2)Clear score\n(3)Clear data\n(4)Forgot password\n(5)Change user pass\n(6)Change admin name\n(7)Change admin password\n(8)Exit\n", 1, 8);
        if (usin == 1)
            edit();
        else if (usin == 2)
            clear_score();
        else if (usin == 3)
            clear_data();
        else if (usin == 4) {
            char usin[100];
            while (1) {
                if (take_username_log(tempuser.username) == -1)
                    break;
                else {
                    char holdpass[100];
                    get_user_pass(tempuser.username, holdpass);
                    printf("User:%s\nPass:%s\n", tempuser.username, holdpass);
                    system("pause");
                    system("cls");
                }
            }
        }
        else if (usin == 5)
            force_change_ps();

        else if (usin == 6) {
            change_admin_name();
        }
        else if (usin == 7) {
            change_admin_pass();
        }
        else if (usin == 8) {
            end_message();
        }
        else if (usin == -1) {
            rlg();
        }
        if (strcmp(admin.username, currentuser.username) != 0)
            break;
        system("cls");
    }
}


int main() {
    checkessfile(); // check if esssential file is lost or not
    load_admin(); // load the current username and passsword for admin
    rlg(); // Register login or guest
    while (1)
    {
        if (strcmp(admin.username, currentuser.username) != 0) {
            menu();
        }
        if (strcmp(admin.username, currentuser.username) == 0) {
            editor();
        }
    }
}