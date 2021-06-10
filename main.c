#include "strprocess.h"
#include "rlg.h"

void display_info(double a, int b,int c, int d){
    printf("a = %lf\nb = %d\nc = %d\nd = %d\n",a,b,c,d);
}

int main(){
    char password[256] = "";
    take_password_reg(password);
    printf("%s",password);
    return 0;
}
