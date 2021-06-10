#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "display.h"
#define ARRAY_SIZE 256

int check_user_exist(char *user) { // check if the user is already exist or not
    FILE* fp;
    char buffer[ARRAY_SIZE], temp[ARRAY_SIZE];
    int find = 0;
    fp = fopen("D:\\QuizGame-RG-C-Project\\userdata.csv", "r");
    while (1) {
        fscanf(fp,"%s",buffer);
        if(strcmp(buffer,user) == 0){
            find = 1;
            break;
        }
        if(fgets(temp, ARRAY_SIZE, (FILE*)fp) == NULL){
            break;
        }
    }
    fclose(fp);
    return find;
}

int check_match(char *username, char *password) { //check if user and passw match
    FILE* fp;
    char buffer[ARRAY_SIZE], temp[ARRAY_SIZE];
    int find = 0;
    fp = fopen("userdata.csv", "r");
    while (1) { // find the same username
        fscanf(fp,"%s",buffer);
        if(strcmp(buffer,username) == 0){
            fscanf(fp,"%s",buffer);
            if(strcmp(buffer,password) == 0){
                find = 1;
                break;
            }
            else{
                break;
            }
        }
        if(fgets(temp, ARRAY_SIZE, (FILE*)fp) == NULL){
            break;
        }
    }
    fclose(fp);
    return find;
}

void load_score(char username[],double *score, int *allq, int *cq, int *wq) {
    char buffer[ARRAY_SIZE];
    if (check_user_exist(username) == 0) {
        color("red");
        printf("User does not exist cannot load score.\n");
        color("reset");
        delay(2);
        return;
    }
    FILE* fp;
    fp = fopen("userdata.csv", "r");
    while (1){
        fscanf(fp,"%s",buffer);
        if (strcmp(buffer, username) == 0){
            fscanf(fp,"%s",buffer); // skip password
            fscanf(fp,"%s",buffer); // read user's score
            *score = strtod(buffer, NULL); //store score(double type)
            fscanf(fp,"%s",buffer); // read user's All question
            *allq = atoi(buffer); // //store All Q(int type)
            fscanf(fp,"%s",buffer); // read user's correct question
            *cq = atoi(buffer);
            fscanf(fp,"%s",buffer); // read user's wrong question
            *wq = atoi(buffer);
            break;
        }
        else{
            fgets(buffer, ARRAY_SIZE, fp);
        }
    }
    fclose(fp);
}