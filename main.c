#include "strprocess.h"
#include "rlg.h"

void display_info(double a, int b,int c, int d){
    printf("a = %lf\nb = %d\nc = %d\nd = %d\n",a,b,c,d);
}

int main(){
    char username[256] = "Kris510", password[256] = "";
    take_password_log(username, password);
    return 0;
}