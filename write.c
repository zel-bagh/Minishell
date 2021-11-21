#include<stdio.h>
#include<stdlib.h>
#include"Minishell.h"

int main()
{
    int id;
    int ex_st;
    id = fork();
    if (id == 0)
        exit(1);
    wait(&ex_st);
    printf("exited with %d\n", ex_st);
}