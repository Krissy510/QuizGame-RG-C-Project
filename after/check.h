/*
ID: 63011293
Name: Raviphas Sananpanichkul
Midterm Project
C PROGRAMMING
Teacher: Ukrit Watchareeruetai
University: King Mongkut's Institute of Technology Ladkrabang
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ARRAY_SIZE 256

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



