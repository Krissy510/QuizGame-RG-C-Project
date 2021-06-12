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
            count++;
        }
        fclose(fp);
        return count;
    }
}

int checkTopicSyntax(char topic[]){
    if(isupper(topic[0]) == 1){
        return 0;
    }
    else{
        return 1;
    }
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
}


//Display

void dis_all_QandA(char topic[]) {
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
}