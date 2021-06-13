#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "display.h"
#define ARRAY_SIZE 256



//Check
int check_user_exist(char *user) { // check if the user is already exist or not
    FILE* fp;
    char buffer[ARRAY_SIZE];
    int find = 0;
    fp = fopen("userdata.txt", "r");
    while (1) {
        fscanf(fp,"%s",buffer);
        if(strcmp(buffer,user) == 0){
            find = 1;
            break;
        }
        if(fgets(buffer, ARRAY_SIZE, fp) == NULL){
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
    fp = fopen("userdata.txt", "r");
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
        if(fgets(temp, ARRAY_SIZE, fp) == NULL){
            break;
        }
    }
    fclose(fp);
    return find;
}

//get
void load_score(struct User *given_user) {
    char buffer[ARRAY_SIZE];
    FILE* fp;
    fp = fopen("userdata.txt", "r");
    while (1){
        fscanf(fp,"%s",buffer);
        if (strcmp(buffer, given_user->username) == 0){
            fscanf(fp,"%s",buffer); // skip password
            fscanf(fp,"%s",buffer); // read user's score
            given_user->score = strtod(buffer, NULL); //store score(double type)
            fscanf(fp,"%s",buffer); // read user's All question
            given_user->allq = atoi(buffer); // //store All Q(int type)
            fscanf(fp,"%s",buffer); // read user's correct question
            given_user->correctq = atoi(buffer);
            fscanf(fp,"%s",buffer); // read user's wrong question
            given_user->wrongq = atoi(buffer);
            break;
        }
        else{
            fgets(buffer, ARRAY_SIZE, fp);
        }
    }
    fclose(fp);
}


//Add data
void regis_user_data(char username[], char password[]) { // register the data to database
    FILE* fp;
    fp = fopen("userdata.txt", "a"); // open the database in append mode
    if (fp == NULL) { // check if there is the database file
        system("cls");
        color("red");
        printf("Userdata is missing.\n");
        color("reset");
        system("pause");
        fclose(fp);
    }
    else { // if the database file exist
        fprintf(fp, "%s\t%s\t0\t0\t0\t0\n", username, password); //print out the format
        fclose(fp); // close the file pointer
    }
}

//remove data
void del_data(char username[]) {
    FILE* fp;
    FILE* cpyfile;
    char read_user[ARRAY_SIZE], read_else[ARRAY_SIZE];
    cpyfile = fopen("temp_del.txt", "w");
    fp = fopen("userdata.txt", "r");
    while (1) { // copy except the given username
        fscanf(fp,"%s", read_user);
        if(fgets(read_else, ARRAY_SIZE, fp) == NULL){
            break;
        }
        else if(strcmp(read_user, username) != 0){
            fprintf(cpyfile, "%s%s", read_user, read_else);
        }
        
    }
    fclose(fp);
    fclose(cpyfile);
    remove("userdata.txt");
    rename("temp_del.txt", "userdata.txt");
}

//edit data for the given user
void update_user(struct User givenUser) {
    FILE* fp;
    FILE* cpyfile;
    char read_user[ARRAY_SIZE], read_else[ARRAY_SIZE];
    cpyfile = fopen("temp_del.txt", "w");
    fp = fopen("userdata.txt", "r");
    while (1) { // copy except the given username
        fscanf(fp,"%s", read_user);
        if(strcmp(read_user, givenUser.username) == 0){
            fprintf(cpyfile, "%s\t", read_user); // write same username
            if(strcmp("None", givenUser.password) == 0){
                fscanf(fp,"%s", read_user); // read password
                fprintf(cpyfile, "%s\t", read_user); // wrtie same password
            }
            else{
                fprintf(cpyfile, "%s\t", givenUser.password);
            }
            fprintf(cpyfile,"%.2lf\t%d\t%d\t%d\n",givenUser.score,givenUser.allq,givenUser.correctq,givenUser.wrongq); // wrtie new data
            if(fgets(read_else, ARRAY_SIZE, fp) == NULL){
                break;
            }
        }
        else{
            if(fgets(read_else, ARRAY_SIZE, fp) == NULL){
                break;
            }
            else{
                fprintf(cpyfile, "%s%s", read_user, read_else);
            }
        }
    }
    fclose(fp);
    fclose(cpyfile);
    remove("userdata.txt");
    rename("temp_del.txt", "userdata.txt");
}
