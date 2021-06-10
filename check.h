#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ARRAY_SIZE 256

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

int check_contain_sp(char str[]) { //check if there is any special characters in the str
    for (int i = 0; i < strlen(str); i++) {
        if(isalnum(str[i]))
            continue;
        else
            return 1;
    }
    return 0;
}

int check_pass_syntax(char *password) { // check if password syntax is correct
    int size = strlen(password);
    if (size > 10 || size <= 0) {
        return 0;
    }
    int check[3] = { 0,0,0 }; //check for all 3 conditions
    for (int index = 0; index < size; index++) {
        if (islower(password[index]) != 0) { // check if the pass include 1 lowercase
            check[0]++;
        }
        else if (isupper(password[index]) != 0) {  // check if the pass include 1 uppercase
            check[1]++;
        }
        else if (isdigit(password[index]) != 0) { // check if the pass include 1 digit
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

int check_value_match_arr(int val, int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}

int check_ban(char str[]) {
    int size = strlen(str);
    for (int i = 0; i < size; i++) {
        if (str[i] == '|')
            return 1;
    }
    return 0;
}

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