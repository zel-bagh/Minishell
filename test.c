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
    struct stat stats;

    p[0]="/Users/zel-bagh//Desktop/Minishell/a.out";
    p[1]=NULL;

    i = stat("/Users/zel-bagh//Desktop/Minishell/writo", &stats);
    if (stats.st_mode & S_IXUSR)
      printf("hi\n");
    //i = execve(p[0],p, NULL);
    //printf(" i= %d and errno = %d\n", i, errno);
}