#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define ARRAY_SIZE 256

//UTILITY

void stringtotextfile(char topic[]) { //change a str topic name to the file format
    int size = strlen(topic);
    if (topic[size - 1] == '\n') {
        size--;
    }
    topic[size] = '.';
    topic[size + 1] = 't';
    topic[size + 2] = 'x';
    topic[size + 3] = 't';
    topic[size + 4] = '\0';
}

void fill_array_random_num(int* ary, int size, int max) {
    int random_num;
    for (int i = 0; i < size; i++) {
        random_num = 1 + rand() % max; // random
        if (i == 0) { // for initial random
            ary[i] = random_num;
        }
        else {
            if ( check_value_match_arr(random_num, ary, i) == 1) { // check if there is a duplicate
                while ( check_value_match_arr(random_num, ary, i) == 1) // while loop for duplicate
                {
                    random_num = 1 + rand() % max; // random the number until it doesn't duplicate
                }
            }
            ary[i] = random_num; // assign it to the array
        }
    }
}

void copyfile(char filePath[], char name[]){
    char read[ARRAY_SIZE];
    FILE *cpy = fopen(name, "w");
    FILE *fp = fopen(filePath, "r");
    while(fgets(read, ARRAY_SIZE, fp) != NULL){
        fprintf(cpy, "%s", read);
    }
    fclose(fp);
    fclose(cpy);
}

//Check/Count
int check_topic_exist(char topic[]) { // check if the topic is already exist or not
    FILE* filepointer;
    int find = 0;
    char read[ARRAY_SIZE];
    filepointer = fopen("topic.txt", "r");
    while (fgets(read, ARRAY_SIZE, filepointer) != NULL) {
        if (read[strlen(read) - 1] == '\n')
            read[strlen(read) - 1] = '\0';
        if (strcmp(read, topic) == 0) {
            find = 1;
            break;
        }
    }
    fclose(filepointer);
    return find;
}

int countQ(char topic[]) {
    char temp_topic[ARRAY_SIZE];
    strcpy(temp_topic, topic);
    stringtotextfile(temp_topic);
    FILE* fp = fopen(temp_topic, "r");
    char read[ARRAY_SIZE];
    int count = 0;
    if (fp == NULL) {
        return -1;
    }
    else {
        while (fgets(read, ARRAY_SIZE, fp) != NULL) {
            fgets(read, ARRAY_SIZE, fp);
            if(strcmp(read," ")!= 0){
                count++;
            }
        }
        fclose(fp);
        return count;
    }
}


int checkTopicSyntax(char topic[]){
    return !(strlen(topic) > 47 || strlen(topic) == 0);
}

int checkfile(char filepath[]){
    int returnVal = 1;
    int count = 0;
    FILE* fp = fopen(filepath, "r");
    if(fp == NULL){ // Check if file exist
        returnVal = 0;
    }
    else{
        char read[ARRAY_SIZE];
        while(1){
            if(fgets(read, ARRAY_SIZE, fp) == NULL){
                if(read[strlen(read)-1] != '\n'){ // Check if end of the text isn't \n
                    returnVal = -1;
                }
                break;
            }
            else{
                count++;
            }
        }   
    }
    if(count%2 != 0){ // Check if Question and  answer is equal
        returnVal = -2;
    }
    fclose(fp);
    return returnVal;
}

//Get

void get_Q(char topic[], int num, char return_question[]) {
    char temp_topic[ARRAY_SIZE];
    strcpy(temp_topic, topic);
    stringtotextfile(temp_topic);
    int count = 1;
    char read[ARRAY_SIZE];
    FILE* filepointer = fopen(temp_topic, "r");
    while (fgets(read, ARRAY_SIZE, filepointer) != NULL)
    {
        if (count == num) {//find the Q
            strcpy(return_question, read);
            break;
        }
        else{
            fgets(read, ARRAY_SIZE, filepointer);
            count++;
        }
    }
    fclose(filepointer);
    int size = strlen(return_question) - 1;
    if(return_question[size] == '\n'){
        return_question[size] = '\0';
    }
}

void get_A(char topic[], int num, char return_answer[]) {
    char temp_topic[ARRAY_SIZE];
    strcpy(temp_topic, topic);
    stringtotextfile(temp_topic);
    int count = 1;
    char read[ARRAY_SIZE];
    FILE* filepointer = fopen(temp_topic, "r");
    fgets(read, ARRAY_SIZE, filepointer);
    while (fgets(read, ARRAY_SIZE, filepointer) != NULL)
    {
        if (count == num) {//find the Q
            strcpy(return_answer, read);
            break;
        }
        else{
            fgets(read, ARRAY_SIZE, filepointer);
            count++;
        }
    }
    fclose(filepointer);
    int size = strlen(return_answer) - 1;
    if(return_answer[size] == '\n'){
        return_answer[size] = '\0';
    }     
}

void getTopic(int num, char returnTopic[], int mode){
    FILE* fp;
    // mode 0 = Not check if Q >= 4
    // mode 1 = Check if Q >= 4
    int count = 1;
    fp = fopen("topic.txt", "r");
    while(1){
        fgets(returnTopic, 47, fp);
        if(mode == 1){
            if(countQ(returnTopic) >= 4){
                if(count == num){
                    break;
                }
                else{
                    count++;
                }
            }
        }
        else{
            if(count == num){
                    break;
                }
                else{
                    count++;
                }
        }
    }
    fclose(fp);
}

//Display
void dis_all_QandA(char topic[], int *reutrnVal) {
    char temp_topic[ARRAY_SIZE], read[ARRAY_SIZE];
    strcpy(temp_topic, topic);
    stringtotextfile(temp_topic);
    FILE *fp = fopen(temp_topic, "r");
    int count = 1;
    while(1){
        if(fgets(read, ARRAY_SIZE, fp) == NULL){
            break;
        }
        else{
            printf("%d. %s", count, read);
            fgets(read, ARRAY_SIZE, fp);
            printf("Answer: %s", read);
            count++;
        }
    }
    if(reutrnVal != NULL){
        *reutrnVal = count-1;
    }
    fclose(fp);
}

void dis_all_topic(int *reutrnVal, int mode){
    // mode 0 = Not check if Q >= 4
    // mode 1 = Check if Q >= 4
    FILE* fp;
    fp = fopen("topic.txt", "r");
    int count = 1;
    char read[47];
    while(1){
        if(fgets(read, 47, fp) == NULL){
            break;
        }
        else{
            if(mode == 0){
                printf("[%d]%s", count, read);
                count++;
            }
            else{
                if(countQ(read) >= 4){
                    printf("[%d]%s", count, read);
                    count++;
                }
            }
        }
    }
    fclose(fp);
    if(reutrnVal != NULL){
        *reutrnVal = count-1;
    }
}

// calculate
int stdq(int am_q) {
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

//edit
void delete_topic(int num_del) {
    FILE* fp, * fpdel;
    char del_name[ARRAY_SIZE];
    int count = 1;
    fpdel = fopen("temp_top_del.txt", "w");
    fp = fopen("topic.txt", "r");
    char read[ARRAY_SIZE];
    while (fgets(read, ARRAY_SIZE, fp) != NULL) {
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
    stringtotextfile(del_name);
    remove(del_name);
}

void create_topic(char topname[]) {
    FILE* fp;
    fp = fopen("topic.txt", "a");
    fprintf(fp, "%s\n", topname);
    fclose(fp);
    stringtotextfile(topname);
    fp = fopen(topname, "w");
    fclose(fp);
}

void delete_QandA(int num_del, char topic[]) {
    FILE* fTemp, * filepointer;
    num_del = (num_del*2) - 1;
    char temp_topic[ARRAY_SIZE], read[ARRAY_SIZE];
    strcpy(temp_topic, topic);
    stringtotextfile(temp_topic);
    fTemp = fopen("temp_del.txt", "w");
    filepointer = fopen(temp_topic, "r");
    int count = 1;
    while (fgets(read, ARRAY_SIZE, filepointer) != NULL) {
        if (count != num_del) {
            fprintf(fTemp, "%s", read);
        }
        else{
            fgets(read, ARRAY_SIZE, filepointer);
        }
        count++;
    }
    fclose(filepointer);
    fclose(fTemp);
    remove(temp_topic);
    rename("temp_del.txt", temp_topic);
}

void add_QandA(char topic[], char question[], char answer[]){
    FILE *fp;
    char temp_topic[ARRAY_SIZE];
    strcpy(temp_topic, topic);
    stringtotextfile(temp_topic);
    fp = fopen(temp_topic, "a");
    fprintf(fp, "%s\n", question);
    fprintf(fp, "%s\n", answer);
    fclose(fp);
}