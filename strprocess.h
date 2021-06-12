#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define ARRAY_SIZE 256

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