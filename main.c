#include "check.h"
#include "dataManager.h"
#include "strprocess.h"

void display_info(double a, int b,int c, int d){
    printf("a = %lf\nb = %d\nc = %d\nd = %d\n",a,b,c,d);
}

int main(){
    char username[256] = "Kris510";
    double score = 0;
    int allq = 0, cq = 0, wq = 0;
    display_info(score,allq,cq,wq);
    load_score(username,&score,&allq,&cq,&wq);
    display_info(score,allq,cq,wq);
    return 0;
}
