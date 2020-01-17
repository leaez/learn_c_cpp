#include <stdlib.h>  
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "share.h"

void b() 
{
    set(123);
    int a = get();
    printf("b get :%d; ",a);
    //sleep(1);
}






