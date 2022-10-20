#include<stdio.h>
#include "add.h"
#include "sub.h"
#include "multi.h"

int main(){
    int a=4;
    int b=3;

    printf("a+b=%d\n", add(a,b));
    printf("a-b=%d\n", sub(a,b));
    printf("a*b=%d\n", multi(a,b));

    return 0;
}
