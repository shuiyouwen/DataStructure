#include <stdio.h>
#include <stdlib.h>

void (*funP)(int);
void myFun(int x);
void (*funA)(int);

int main()
{
    myFun(10);
    funP = &myFun;
    (*funP)(200);
    funA = myFun;
    funA(300);
}

void myFun(int x)
{
    printf("myFun: %d\n", x);
}