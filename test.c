#include "Minishell.h"
#include <readline/history.h>

void    function()
{
  static int d=0;

  d++;
  printf("%d\n", d);
}

int main(int argc, char **argv)
{
    char **p = malloc(2 * sizeof(char *));
    int a[100];
    int i;

    p[0] = "./yo.c";
    p[1] = NULL;

    pipe(a);
    dup2(1,a[1]);
    dup2(0,a[0]);


    while(1);// i = execve("./a.out", p, NULL);
    // printf("i == %d\n", errno);
    //i = execve("./khikho", p, NULL);
    open("directory", O_RDONLY | O_APPEND);
    printf("i == %d\n",errno);
}