/*
ID: 63011293
Name: Raviphas Sananpanichkul
Midterm Project
C PROGRAMMING
Teacher: Ukrit Watchareeruetai
University: King Mongkut's Institute of Technology Ladkrabang
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<time.h>
#define pass_length 9
#define user_length 5
#define array_length 10000

//global variable
char choice[100];
char temp[array_length];
char read[array_length];
struct usinfo {
    char username[100];
    char  password[100];
    int wq;
    int cq;
    double allq;
    double score;
} currentuser, tempuser, admin;


//display func
void welcome() { // show a warm welcome to the current user
    system("cls");
    printf("\033[0;32mHello,\033[0m %s\n", currentuser.username);
    printf("\033[0;36mWelcome to Kris PG's quiz game!\033[0m\n");
    system("pause");
    system("cls");
}
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
    // Storing start time
    clock_t start_time = clock();
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
void pass_syntax_guide() { //display the password correct syntax
    printf("Please enter 9 characters.\n");
    printf("Use only alphabet or numbers.\n");
    printf("It should contain at least 1 capital letter.\n");
    printf("It should contain at least 1 lower case letter.\n");
    printf("It should contain at least 1 digit.\n");
    printf("\033[1;31mPassword should not contain any special characters.\033[0m\n");
}
void end_message() {
    system("cls");
    printf("\033[0;32mThank you for playing, see you next time!\033[0m\n");
    exit(0);
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
    system("pause");
}
void disp_qanda(char str[]) {
    int size = strlen(str);
    char ch;
    for (int i = 0; i < size; i++) {
        ch = str[i];
        if (ch != '\\') {
            putchar(ch);
        }
        else {
            if ((i + 1) != size) {
                ch = str[i + 1];
                if (ch == 'n') {
                    printf("\n");
                    i++;
                }
                else {
                    printf("%c", str[i]);
                }
            }
            else {
                putchar(ch);
            }
        }
    }
    printf("\n");
}
void red() {
    printf("\033[1;31m");
}
void green() {
    printf("\033[0;32m");
}
void reset_color() {
    printf("\033[0m");
}


// check func
int check_if_sp(char str[]) { //check if there is any special characters in the str
    for (int i = 0; i < strlen(str); i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
            continue;
        else
            return 1;
    }
    return 0;
}
int check_user_exist(char user[]) { // check if the user is already exist or not
    FILE* fpuserdata;
    char* token;
    fpuserdata = fopen("userdata.csv", "r");
    while (fgets(read, array_length, fpuserdata) != NULL) {
        token = strtok(read, ",");
        if (strcmp(token, user) == 0) {
            fclose(fpuserdata);
            return 1;
        }
    }
    fclose(fpuserdata);
    return 0;
}
int check_pass(char passw[]) { // check if password syntax is correct
    int size = strlen(passw);
    if (size != 9) {
        return 0;
    }
    int check[3] = { 0,0,0 }; //check for all 3 conditions
    for (int loop = 0; loop < size; loop++) {
        if (islower(passw[loop]) != 0) { // check if the pass include 1 lowercase
            check[0]++;
        }
        else if (isupper(passw[loop]) != 0) {  // check if the pass include 1 uppercase
            check[1]++;
        }
        else if (isdigit(passw[loop]) != 0) { // check if the pass include 1 digit
            check[2]++;
        }
    }
    if (check[0] != 0 && check[1] != 0 && check[2] != 0) {
        return 1;
    }
    else {
        return 0;
    }
}
int check_match(char username[], char passw[]) { //check if user and passw match
    char* token;
    FILE* filematch;
    filematch = fopen("userdata.csv", "r");
    while (fgets(read, array_length, filematch) != NULL) { // find the same username
        token = strtok(read, ",");
        if (strcmp(token, username) == 0) { // if it finds the same username
            token = strtok(NULL, ",");  // Get the password in the database
            if (strcmp(token, passw) == 0) { // if password also matches
                fclose(filematch);
                return 1;
            }
            else // because there can be only one username and if the password doesn't match then the password is wrong
                break;
        }
    }
    fclose(filematch);
    return 0;
}
void checkessfile() { //Check if the essential file is there
    FILE* check1, * check2, * check3;
    check1 = fopen("userdata.csv", "r");
    check2 = fopen("topic.txt", "r");
    check3 = fopen("admin.txt", "r");
    if (check1 == NULL) {
        check1 = fopen("userdata.csv", "w"); //if not create it
    }
    if (check2 == NULL) {
        check2 = fopen("topic.txt", "w");//if not create it
    }
    if (check3 == NULL) {
        check3 = fopen("admin.txt", "w");//if not create it
        fprintf(check3, "ADMINSP\nAdmin1234");
    }
    fclose(check1);
    fclose(check2);
    fclose(check3);
}
int valueinarray(int val, int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}
void fill_array_random_num(int* ary, int size, int maxi) {
    int random_num;
    for (int i = 0; i < size; i++) {
        random_num = 1 + rand() % maxi;
        if (i == 0) {
            ary[i] = random_num;
        }
        else {
            if (valueinarray(random_num, ary, i) == 1) {
                while (valueinarray(random_num, ary, i) == 1)
                {
                    random_num = 1 + rand() % maxi;
                }
            }
            ary[i] = random_num;
        }
    }
}
int check_ban(char str[]) {
    int size = strlen(str);
    for (int i = 0; i < size; i++) {
        if (str[i] == '|')
            return 1;
    }
    return 0;
}
int check_QandA(char fn[]) {
    FILE* fp = fopen(fn, "r");
    while (fgets(read, array_length, fp) != NULL) {
        int check_for = 0;
        for (int i = 0; i < strlen(read); i++) {
            if (read[i] == '|')
                check_for++;
            if (check_for > 1) {
                fclose(fp);
                return i;
            }
        }
    }
    return 0;
}
int findvalinarr(int arr[], int size, int val) {
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == val)
            return i + 1;
    }
    return -1;
}
int check_topic_exist(char topic[]) { // check if the topic is already exist or not
    FILE* filepointer;
    filepointer = fopen("topic.txt", "r");
    while (fgets(read, array_length, filepointer) != NULL) {
        if (read[strlen(read) - 1] == '\n')
            read[strlen(read) - 1] = '\0';
        if (strcmp(read, topic) == 0) {
            fclose(filepointer);
            return 1;
        }
    }
    fclose(filepointer);
    return 0;
}


// change val func
void change_topictofile(char topic[]) { //change a str topic name to the file format
    int size = strlen(topic);
    if (topic[size - 1] == '\n') {
        size--;
    }
    topic[size] = 'Q';
    topic[size + 1] = '.';
    topic[size + 2] = 't';
    topic[size + 3] = 'x';
    topic[size + 4] = 't';
    topic[size + 5] = '\0';
}
void load_score_temp(char username[]) {
    char* token;
    if (check_user_exist(username) == 0) {
        printf("\033[0;34mUser does not exist cannot load score.\033[0m\n");
        delay(2);
        return;
    }
    FILE* fileload;
    fileload = fopen("userdata.csv", "r");
    while (fgets(read, array_length, fileload) != NULL) { // find the same username
        token = strtok(read, ","); //get username
        if (strcmp(token, username) == 0) { // if it finds the same username
            token = strtok(NULL, ",");  // Read pass the password
            token = strtok(NULL, ","); // get score
            tempuser.score = strtod(token, NULL); // send score to var
            token = strtok(NULL, ","); //get allq
            tempuser.allq = strtod(token, NULL);// send allq to var
            token = strtok(NULL, ",");//get correct q
            tempuser.cq = atoi(token);// send correct q to var
            token = strtok(NULL, "\n");//get wrong q
            tempuser.wq = atoi(token);// send correct q to var
            break;
        }
    }
    fclose(fileload);
}
void load_score_current() {
    currentuser.score = tempuser.score, currentuser.allq = tempuser.allq, currentuser.cq = tempuser.cq, currentuser.wq = tempuser.wq;
}


//user input function
int take_username_reg(char user[]) { //ask user to for their new username
    char username[100];
    printf("Please enter only 5 characters!\nUse only alphabet or numbers.\n");
    printf("If you want to go back enter '/back'\n");
    printf("Username:");
    gets(username); // ask for a new user name
    if (strcmp(username, "/back") == 0)  // if user want to go back to the choosing of login regis or guest
        return -1;
    if (strlen(username) != user_length || check_user_exist(username) == 1 || check_if_sp(username) == 1)
        while (1) {
            system("cls");
            printf("\033[1;31mError!\n");
            if (strlen(username) != user_length)
                printf("Please enter only 5 characters!\n");
            else if (check_user_exist(username) == 1)
                printf("The user is already exist!\n");
            if (check_if_sp(username) == 1)
                printf("Please use only alphabet or numbers.\n");
            printf("\033[0mIf you want to go back enter '/back'\n");
            printf("Username:");
            gets(username);
            if (strcmp(username, "/back") == 0)
                return -1;
            if (strlen(username) == user_length && check_user_exist(username) == 0 && check_if_sp(username) == 0) // if all condition met then break
                break;
        }
    system("cls");
    strcpy(user, username); //copy the string into the entered string
    return 1; // finish process
}
void get_pass(char passw[]) { // ask and encrypt the password
    char ch;
    int i = 0;
    while (1) {
        ch = getch();
        if (ch == 13 || ch == 9) { //Enter = 13 Tab = 9
            passw[i] = '\0';
            break;
        }
        else if (ch == 8) {//BKSP = 8
            if (i > 0) {
                i--;
                printf("\b \b"); // \b = backspace
            }
        }
        else {
            passw[i++] = ch;
            printf("*");
        }
    }
    printf("\n");
}
int take_password_reg(char password[]) {
    char passw[100], temp[100];
    while (1) { //big loop if user want to go back from confirmation stage
        while (1) {
            pass_syntax_guide();// Display the format that how the password should be
            printf("If you want to go back enter '/back'\n");
            printf("Password:");
            get_pass(passw); //Ask user for a pass word then decrypt it
            system("cls"); // Screen cleared
            if (strcmp(passw, "/back") == 0)// if the user wants to go back to the username part
                return -1;
            if (check_pass(passw) == 1 && check_if_sp(passw) == 0)
                break; //it will process to the next loop
            else {
                printf("\033[1;31mERROR:\033[0m\n");
                if (check_pass(passw) == 0)
                    printf("\033[1;31mInvalid password format.\033[0m\n");
                if (check_if_sp(passw) == 1)
                    printf("\033[1;31mPassword should not contain any special characters.\033[0m\n");
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
            else if (strcmp(temp, passw) == 0) { // if password match
                system("cls");
                strcpy(password, passw);
                return 1; // end of this func
            }
            else // if not matched then it will still loop until user enter match or enter /back
                system("cls");
        }
    }
}
int user_choice(char display[], int min_val, int max_val) { //choice format with /back func
    char choice[100];
    while (1) {
        printf("%s", display);
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
int take_username_log(char user[]) { //Ask user username for login
    char username[100];
    while (1) {
        printf("\033[0mIf you want to go back enter '/back'\n"); //reset color
        printf("Username:");
        gets(username);
        system("cls");
        if (strcmp(username, admin.username) == 0) {// Special case
            strcpy(user, username);
            return 1;
        }
        if (strcmp(username, "/back") == 0) // return user back to rlg
            return -1;
        if (strlen(username) == user_length && check_user_exist(username) == 1 && check_if_sp(username) == 0)
            break;
        printf("\033[1;31mERROR:\n");
        if (strlen(username) != user_length)
            printf("Please enter only 5 characters!\n");
        else if (check_user_exist(username) == 0)
            printf("This user does not exist!\n");
        if (check_if_sp(username) == 1)
            printf("Please use only alphabet or numbers.\n");
    }
    strcpy(user, username);
    return 1; //Finished
}
int take_password_log(char user[], char password[]) { //Ask user password for login
    char passw[100];
    while (1) {
        printf("If you want to go back enter '/back'\n");
        printf("Username:%s\n", user);
        printf("Password:");
        get_pass(passw);
        system("cls");
        if (strcmp(passw, "/back") == 0)
            return -1;
        if (check_pass(passw) == 1 && check_if_sp(passw) == 0) // check format
            break;
    }
    strcpy(password, passw);
    return 1;
}

//get val from file
void get_Q(char topic[], int num, char question[]) {
    FILE* filepointer;
    int count = 1;
    char* token;
    filepointer = fopen(topic, "r");
    while (fgets(read, array_length, filepointer) != NULL)
    {
        if (count == num) {//find the Q
            token = strtok(read, "|");
            strcpy(question, token);
            break;
        }
        count++;
    }
    fclose(filepointer);
}
void get_A(char topic[], int num, char answer[]) {
    int count = 1;
    char* token;
    FILE* filepointer;
    filepointer = fopen(topic, "r");
    while (fgets(read, array_length, filepointer) != NULL)
    {
        if (count == num) {//find the A
            token = strtok(read, "|");
            token = strtok(NULL, "\n");
            strcpy(answer, token);
            break;
        }
        count++;
    }
    fclose(filepointer);
}
int get_rank(char user[]) {
    FILE* getrank;
    char* token;
    int count = 0;
    getrank = fopen("userdata.csv", "r");
    while (fgets(read, array_length, getrank) != NULL) {
        count++;
        token = strtok(read, ",");
        if (strcmp(token, user) == 0) {
            fclose(getrank);
            return count;
        }
    }
    fclose(getrank);
    return 0;
}
int count_data() { //check if data exist
    FILE* filepointer;
    int count = 0;
    filepointer = fopen("userdata.csv", "r");
    while (fgets(read, array_length, filepointer) != NULL) {
        count++;
    }
    fclose(filepointer);
    return count;
}
int countQ(char tp[]) {
    FILE* fp = fopen(tp, "r");
    int count = 0;
    if (fp == NULL) {
        system("cls");
        printf("\033[0;31mThe topic file doesn't exist.\033[0m\n");
        system("pause");
        system("cls");
        return -1;
    }
    else {
        while (fgets(read, array_length, fp) != NULL) {
            count++;
        }
        fclose(fp);
        return count;
    }
}
int stdq(char topic[]) {
    int am_q = countQ(topic);
    if (am_q < 10)
    {
        return am_q;
    }
    else if (am_q >= 10 && am_q <= 20) {
        return am_q * 4 / 5;
    }
    else {
        int p = 80;
        for (int loop = 0; loop < (am_q / 10); loop++) {
            p -= (p / 8);
        }
        return am_q * p / 100;
    }
}
void dis_all_QandA(char topic[], int am_q, int* p_q) {
    system("cls");
    char question[500], answer[500];
    for (int index_Q = 0; index_Q < am_q; index_Q++)
    {
        get_Q(topic, p_q[index_Q], question);
        get_A(topic, p_q[index_Q], answer);
        printf("%d.\nQ:%s\n", index_Q + 1, question);//display question
        printf("A:%s\n\n", answer); //display answer
    }
    system("pause");
    system("cls");
}

//file process func
void regis_user_data(char username[], char passw[]) { // regis ter the data to the database
    FILE* fileregis;
    fileregis = fopen("userdata.csv", "a"); // open the database in append mode
    if (fileregis == NULL) { // check if there is the database file
        system("cls");
        printf("\033[0;34mUserdata is missing.\033[0m\n");
        system("pause");
        fclose(fileregis);
    }
    else { // if the database file exist
        fprintf(fileregis, "%s,%s,0,0,0,0\n", username, passw); //print out the format
        fclose(fileregis); // close the file pointer
    }
}
void del_data(char user[]) {
    FILE* filepointer;
    FILE* cpyfile;
    char* token;
    cpyfile = fopen("temp_del.csv", "w");
    filepointer = fopen("userdata.csv", "r");
    while (fgets(read, array_length, filepointer) != NULL) { // copy except the new username
        strcpy(temp, read);
        token = strtok(temp, ",");
        if (strcmp(token, user) != 0)
            fprintf(cpyfile, "%s", read);
    }
    fclose(filepointer);
    fclose(cpyfile);
    remove("userdata.csv");
    rename("temp_del.csv", "userdata.csv");
}
void sortLeader() {
    //find user with the max score
    // write it in the new file then del the old data in the file
    // repeat the step until all file in userdata are NULL
    struct usinfo maxuser, readuser;
    char read[100], temp[100];
    FILE* fTemp, * fpread;
    char* token;
    fTemp = fopen("temp_sort.csv", "w");
    while (count_data() != 0) {
        fpread = fopen("userdata.csv", "r");
        int count = 0;
        while (fgets(read, array_length, fpread) != NULL) {
            strcpy(temp, read);
            if (count == 0) { //initializing
                token = strtok(temp, ",");
                strcpy(maxuser.username, token);
                token = strtok(NULL, ",");
                strcpy(maxuser.password, token);
                token = strtok(NULL, ",");
                maxuser.score = strtod(token, NULL);
                count = 1;
            }
            else {
                token = strtok(temp, ",");
                strcpy(readuser.username, token);
                token = strtok(NULL, ",");
                strcpy(readuser.password, token);
                token = strtok(NULL, ",");
                readuser.score = strtod(token, NULL);
                if (readuser.score > maxuser.score) {
                    strcpy(maxuser.username, readuser.username);
                    strcpy(maxuser.password, readuser.password);
                    maxuser.score = readuser.score;
                }
            }
        }
        fclose(fpread);
        load_score_temp(maxuser.username);
        fprintf(fTemp, "%s,%s,%lf,%lf,%d,%d\n", maxuser.username, maxuser.password, tempuser.score, tempuser.allq, tempuser.cq, tempuser.wq);
        del_data(maxuser.username);
    }
    fclose(fTemp);
    remove("userdata.csv");
    rename("temp_sort.csv", "userdata.csv");
}
void update_user(char user[], char passw[], double score, double allq, int cq, int wq) { // find user and change their score at will
    if (strcmp(user, "TEMP GUEST") == 0) // since guest don't have any data base anyway
        return;
    char* token;
    FILE* fTemp, * fpdata;
    fTemp = fopen("temp_cpy.csv", "w");
    fpdata = fopen("userdata.csv", "r");
    while (fgets(read, array_length, fpdata) != NULL) {
        strcpy(temp, read); //copy so that read will not be damage
        token = strtok(temp, ",");
        if (strcmp(token, user) == 0) { // if user match
            fprintf(fTemp, "%s,", token); //copy username to the temp file
            token = strtok(NULL, ",");//pass the password
            fprintf(fTemp, "%s,", passw);//write new password
            fprintf(fTemp, "%lf,%lf,%d,%d\n", score, allq, cq, wq); //write new score
        }
        else // if user not match then copy the whole data to the temp file
            fprintf(fTemp, "%s", read);
    }
    fclose(fpdata);
    fclose(fTemp);
    remove("userdata.csv"); //delete old data base
    rename("temp_cpy.csv", "userdata.csv"); // rename the temp file to be the new database
    sortLeader();
}

//medium func
int regis() { // final func for reg
    system("cls");
    while (1) {
        if (take_username_reg(currentuser.username) == -1) //go back to rlg
            return -1;
        else if (take_password_reg(currentuser.password) == -1) //go back to username reg
            system("cls");
        else // take password and user name has been succeed
            break;
    }
    system("cls");
    regis_user_data(currentuser.username, currentuser.password);
    currentuser.wq, currentuser.cq = 0, 0;
    currentuser.allq, currentuser.score = 0, 0;
    printf("\033[0;32mSuccesfully register user as %s\033[0m\n", currentuser.username);
    delay(1);
    return 1; //finished all process
}
int login() { //final func for login
    while (1) { // big loop to catch if not match
        while (1) { // loop for getting user and password
            if (take_username_log(currentuser.username) == -1)
                return -1; //user wants to go back to rlg
            else if (take_password_log(currentuser.username, currentuser.password) == -1)
                system("cls");//user wants to go back to take user log
            else // The format of username or password is correct
                break;
        }
        system("cls");
        if (check_match(currentuser.username, currentuser.password) == 1) //if check that they matched
            break;
        else if (strcmp(currentuser.username, admin.username) == 0 && strcmp(currentuser.password, admin.password) == 0) {
            return 1; //ADMIN login
        }
        else { // the user and password doesn't match
            printf("\033[0;34mSorry, incorrect Username or Password.\033[0m\nPlease try again.\n");
        }
    }
    load_score_temp(currentuser.username);//load the user's score
    load_score_current();
    printf("\033[0;32mSuccessfully login user as %s\033[0m\n", currentuser.username); // display a confirm message
    delay(1);
    return 1;//Finished
}
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
void disleaderboard() { //dafuq
    FILE* filepointer;
    double readscore;
    system("cls");
    int count = 1;
    filepointer = fopen("userdata.csv", "r");
    char* token;
    while (fgets(read, array_length, filepointer) != NULL && count < 11) {
        token = strtok(read, ",");
        if (read[0] != '\n') {
            printf("Rank:%d\nUsername:%s\n", count, token);
            token = strtok(NULL, ",");
            token = strtok(NULL, ",");
            readscore = strtod(token, NULL);
            printf("Total_score: %02.2lf\n\n", readscore);
            count++;
        }
    }
    fclose(filepointer);
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