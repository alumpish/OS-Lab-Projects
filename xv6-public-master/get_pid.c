#include "types.h"
#include "user.h"

int main(int argc , char* argv[]){
    /*if(argc !=1){
       printf(1,"wrong format");
       exit(); 
    }*/
    int pid = getpid();

    printf(1, "PID : %d",pid);

    exit();

}