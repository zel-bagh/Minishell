#include "Minishell.h"
#include <readline/history.h>


int main()
{
    char *p;
    char a[100];

     read(0, a, 10);
    write(1, a, 10);
}