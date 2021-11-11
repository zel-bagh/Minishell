#include<stdio.h>
#include"Minishell.h"
#include<limits.h>

char    *ft_itoa_positif(int i, int counter)
{
    char *string;

    string = malloc((counter + 1) * sizeof(char));
    string[counter] = '\0';
    string = string + counter - 1;
    while(i / 10 != 0)
    {
        *string = (i % 10) + 48;
        i = i / 10;
        string--;
    }
    *string = i + 48;
    return (string);
}

char    *ft_itoa_negatif(unsigned int j, int counter)
{
    char *string;

    string = malloc((counter + 2) * sizeof(char));
    string[counter - 1] = '\0';
    *string = '-';
    string = string + counter;
    while(j / 10 != 0)
    {
        *string = (j % 10) + 48;
        j = j / 10;
        string--;
    }
    *string = j + 48;
    string--;
    return (string);
}

char    *ft_itoa(int i)
{
    int             counter;
    unsigned int    j;
    char            *string;

    j = i;
    if (i < 0)
        j = -i;
    counter = 1;
    while (j / 10 != 0)
    {
        counter++;
        j = j / 10;
    }

    if (i >= 0)
        string = ft_itoa_positif(i, counter);
    else 
        string = ft_itoa_negatif(-i, counter);
    return (string);
}
int main()
{
        printf("%s\n", ft_itoa(1));
        printf("%s\n", ft_itoa(-1));
        printf("%s\n", ft_itoa(INT_MAX));
        printf("%s\n", ft_itoa(INT_MIN));
}
