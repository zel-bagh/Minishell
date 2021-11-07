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
    char a[100];
    int i;

    p[0] = "./yo.c";
    p[1] = NULL;

    // i = execve("./a.out", p, NULL);
    // printf("i == %d\n", errno);
    i = execve("./khikho", p, NULL);
    printf("i == %d\n",errno);
}