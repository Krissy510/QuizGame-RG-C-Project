#include "strprocess.h"
#include "rlg.h"

int main(){
    char username[ARRAY_SIZE] = "Kris510", password[ARRAY_SIZE] = ""; 
    char topic[ARRAY_SIZE] = "testTopic", question[ARRAY_SIZE] = "";
    get_A(topic, 1, question);
    printf("%s", question);
    return 0;
}