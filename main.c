#include "rlg.h"
#include "qaManager.h"

void checkessfile() { //Check if the essential file is there
    FILE* check1, * check2, * check3;
    check1 = fopen("userdata.txt", "r");
    check2 = fopen("topic.txt", "r");
    if (check1 == NULL) {
        check1 = fopen("userdata.txt", "w"); //if not create it
        regis_user_data("Guest","Guest"); //Guest account
        regis_user_data("root", "toor"); //Admin account
    }
    if (check2 == NULL) {
        check2 = fopen("topic.txt", "w");//if not create it
    }
    fclose(check1);
    fclose(check2);
}



int main(){
    struct User temp;
    guest(&temp);
    dis_guest_info(temp);
    return 0;
}