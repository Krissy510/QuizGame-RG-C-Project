#include "page.h"
#include <time.h>

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
    srand(time(0)); //new seed
    struct User mainUser;
    char topic[47];
    int amount, progress, process, mode;
    system("cls");
    while(1){
        process = entryPage(&mainUser);
        if(process == -1){
            break;
        }
        else if(process == 1){
            while(1){
                process = menu(&mainUser);
                if(process == 1){
                    if(playPage(topic,&amount, &mode) == 1){
                        if(mode == 1){
                            quizGame(topic,amount,&mainUser,0);
                        }
                        else if(mode == 2){
                            type_it_out(topic,amount,&mainUser);
                        }
                        else if(mode == 3){
                            quizGame(topic,amount,&mainUser,1);
                        }
                    }
                }
                else if(process == 2){
                    guide(0);            
                } 
                else if(process == 3){
                    userInfo(mainUser);
                }
                else if(process == 4){
                    system("cls");
                    break;
                }
                else if(process == 5){
                    changePassword(&mainUser);
                }
                else if(process == 6){
                    end_message();
                    return 0;
                }
            }
        }
        else if(process == 2){
            while(1){
                process = editorMenu();
                if(process == 1){
                    edit();
                }
                else if(process == 2){
                    guide(1);            
                } 
                else if(process == 3){
                    forceChangePass();
                }
                else if(process == 4){
                    clear_remove_data();
                }
                else if(process == 5){
                    system("cls");
                    break;
                }
                else if(process == 6){
                    end_message();
                    return 0;
                }
            }
        
        }
    }    
    end_message();
    return 0;
}