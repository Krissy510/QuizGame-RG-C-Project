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
    topic[size] = 'Q';
    topic[size + 1] = '.';
    topic[size + 2] = 't';
    topic[size + 3] = 'x';
    topic[size + 4] = 't';
    topic[size + 5] = '\0';
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