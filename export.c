/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:13:14 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/22 19:54:44 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Minishell.h"

int number(char **args)
{
    int n;

    n = 0;
    while (args[n])
        n++;
    return (n);
}

int nbr_remained_args(t_argument *header)
{
    int n;

    n = 1;
    while(header->next)
    {
        n++;
        header = header->next;
    }
    return(n);
}

void    add_to_list(char *arg, t_argument **header)
{
    t_argument *last;
    
    if (!*header)
    {
        *header = malloc(1 * sizeof(t_argument));
        (*header)->argument = arg;
        (*header)->next = NULL;
    }
    else
    {
        last = *header;
        while(last->next)
            last = last->next;
        last->next = malloc(1 * sizeof(t_argument));
        last->next->argument = arg;
        last->next->next = NULL;        
    }
}

int are_args_ingood_form(char **args, t_argument **header, int *k)
{
    int i;
    int j;
    
    i = -1;
    j = -1;
    *k = 0;
    while (args[++i])
    {
        while (args[i][++j] != '=' && args[i][++j])
        {
            if ((j == 0 && args[i][j] >= 48 && args[i][j] <= 57) || ((
                args[i][j] < 48 || args[i][j] > 57) && (args[i][j] < 65
             || args[i][j] > 90) && (args[i][j] < 97 || args[i][j] > 122)
              && args[i][j] != '_'))
            {
                printf("Minishell: export: `%s': not a valid identifier\n",
                args[i]);
                *k = 1;
                break ;
            }
        }
        if (args[i][j] == '=' || args[i][j] == '\0')
            add_to_list(args[i], header);
    }
}

char*   copy_string(char *string)
{
    int n;
    char *new_string;
    int i;
    
    i = -1;
    n = ft_strlen(string);
    new_string = malloc((n + 1) * sizeof(char));
    while (string[++i])
        new_string[i] = string[i];
    new_string[i] ='\0';
    return (new_string);
}

int    compaire_arg_env(char *argument, char *env)
{
    int j;
    int k;

    j = -1;
    k = -1;
    while (env[++j] != '=' && env[j] && argument[++k] != '=' && argument[k])
        if (env[j] != argument[k])
            break ;
    if ((!env[j] || env[j] == '=') && (!argument[k] || argument[k] == '='))
    {
        if (argument[k] == '=')
            return (2);
        return (1);
    }
    return (0);
}

t_argument*   delete_node(t_argument *node, t_argument **header)
{
    t_argument *p;
    
    if (node == *header)
    {
        *header = (*header)->next;
        free(node);
        return (*header);
    }
    else
    {
        p = *header;
        while(p->next != node)
            p= p->next;
        p->next = node->next;
        free(node);
        return (p->next);
    }
}

void    change_env(char *arg, char **env)
{
    free(env[0]);
    env[0] = copy_string(arg);
}

void    change_already_existed_env(t_argument **header, char **env)
{
    int i;
    int j;
    t_argument *p;

    p = *header;
    while (1)
    {
        i = -1;
        while (env[++i])
        {
            j = compaire_arg_env(p->argument, env[i]);
            if (j != 0)
            {
                if (j == 2)
                    change_env(p->argument, env + i);
                p = delete_node(p, header);
                break ;
            }
            if (!env[i + 1])
                p = p->next;
        }
        if (!p)
            break ;
    }
}

int    copy_old_env(char **new_env, char **env)
{
    int i;

    i = -1;
    while (env[++i])
        new_env[i] = env[i];
    free(env);
    return (i);
}

void    add_new_env(char **new_env, t_argument **header, int i)
{
    t_argument *p;

    p = *header;
    while (1)
    {
        new_env[i++] = copy_string(p->argument);
        p = delete_node(p, header);
        if (!p)
         break ;
    }
    new_env[i] = NULL;
}

int  export(char **args, int input, int output, char ***env)
{
    int i;
    char **new_env;
    t_argument *header;

    if (!args[0])
    {
        printf("i should show env\n");
        return(0);
    }
    are_args_ingood_form(args, &header, &i);
    if (!header)
        return(1);
    if (env[0])
        change_already_existed_env(&header, *env);
    if (!header && i)
        return (1);
    if (!header && !i)
        return (0);
    new_env = malloc((number(*env) +
        nbr_remained_args(header) + 1) * sizeof(char *));
    add_new_env(new_env, &header, copy_old_env(new_env, env));
    *env = new_env;
    if (i)
        return (1);
    return (0);
}