
#include <stdlib.h>  
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "share.h"

static int fd;

void a () {
    fd++;
    printf("a get :%d; ",fd);
    //sleep(1);
}
int get(){
    return fd;
}
void set(int a){
    fd =a;
}






