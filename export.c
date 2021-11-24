/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:13:14 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/24 16:59:03 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Minishell.h"

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

int    copy_old_env(char **new_env, char **env)
{
    int i;

    i = -1;
    while (env[++i])
        new_env[i] = env[i];
    free(env);
    return (i);
}

char**    add_pwd(char **env)
{
    char **new_env;
    int i;
    
    new_env = malloc((number(env) + 2) * sizeof(char *));
    i = -1;
    while(env[++i])
        new_env[i] = env[i];
    new_env[i] = copy_string("OLDPWD");
    new_env[++i] = NULL;
    free(env);
    return (new_env);
}

void    change_env_to_heap(char ***env)
{
    char **new_env;
    char **p;
    int i;
    int oldpwd;

    oldpwd = 0;
    p = *env;
    i = -1;
    new_env = malloc((number(p) + 1) * sizeof(char *));
    while(p[++i])
    {
        if (ft_compaire("OLDPWD", p[i]) == 2 && ++oldpwd)
        {
            new_env[i] = copy_string("OLDPWD");
        }
        new_env[i] = copy_string(p[i]);
    }
    
    new_env[i] = NULL;
    *env = new_env;
    if (!oldpwd)
        *env = add_pwd(new_env);
}

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

void are_args_ingood_form(char **args, t_argument **header, int *k)
{
    int i;
    int j;
    
    i = -1;
    *k = 0;
    *header = NULL;
    while (args[++i])
    {
        j = -1;
        while (args[i][++j] != '=' && args[i][j])
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

int    compaire_arg_env(char *argument, char *env)
{
    int j;
    int k;

    j = -1;
    k = -1;
    while (env[++j] != '=' && env[j] && argument[++k] != '=' && argument[k])
        if (env[j] != argument[k])
            break ;
    if ((!env[j] || env[j] == '=') && (!argument[j] || argument[j] == '='))
    {
        if (argument[j] == '=')
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

void    copy_env(char **new_env, char **env)
{
    int i;

    i = -1;
    while(env[++i])
        new_env[i] = env[i];
    new_env[i] = NULL;
}

void    ft_free(char *a, char *b)
{
    free(a);
    free(b);
}

char*   get_key(char *p)
{
    int i;
    char *a;

    i = 0;
    while (p[i] != '=' && p[i])
        i++;
    a = malloc((i  + 1) * sizeof(char));
    i = -1;
    while (p[++i] != '=' && p[i])
        a[i] = p[i];
    a[i] = '\0';
    return (a);
}

int ft_compaire(char *a, char *b)
{
    char *ta;
    char *tb;
    int i;

    ta = get_key(a);
    tb = get_key(b);
    i = -1;
    while(ta[++i] != '\0' || tb[i] != '\0')
    {
        if (ta[i] < tb[i])
        {
            ft_free(ta, tb);
            return (0);               
        }
        if (ta[i] > tb[i])
        {
            ft_free(ta, tb);
            return(1);
        }
    }
    ft_free(ta, tb);
    return(2);
}

void    ft_write(char *a, int output)
{
    int i;

    i = -1;
    while (a[++i] != '=' && a[i])
        write(output, a + i, 1);
    if (a[i] == '=')
    {
        write(output, "=\"", 2);
        while (a[++i])
            write(output, a + i, 1);
        write(output, "\"", 1);
    }
}

void    show(char **env, int output)
{
    int i;

    i = -1;
    while (env[++i])
    {
        write(output, "declare -x ", 11);
        ft_write(env[i], output);
        write(output, "\n", 1);
    }
    free(env);
}

int    show_env(char **env, int input, int output)
{
    char **sorted_env;
    int i;
    int j;
    char *tmp;

    i = -1;
    sorted_env = malloc((number(env) + 1 ) * sizeof(char *));
    copy_env(sorted_env, env);
    while (sorted_env[++i])
    {
        j = i;
        while (sorted_env[++j])
        {
            if (ft_compaire(sorted_env[i], sorted_env[j]))
            {
                tmp = sorted_env[j];
                sorted_env[j] = sorted_env[i];
                sorted_env[i] = tmp;
            }
        }
    }
    input = 0;
    show(sorted_env, output);
    return (1);
}

int  export(char **args, int input, int output, char ***env)
{
    int i;
    char **new_env;
    t_argument *header;

    if (!args[0] && show_env(*env, input, output))
        return(0);
    are_args_ingood_form(args, &header, &i);
    if (!header)
        return(1);
    if (env[0][0])
        change_already_existed_env(&header, *env);
    if (!header && i)
        return (1);
    if (!header && !i)
        return (0);
    new_env = malloc((number(*env) +
        nbr_remained_args(header) + 1) * sizeof(char *));
    add_new_env(new_env, &header, copy_old_env(new_env, *env));
    *env = new_env;
    if (i)
        return (1);
    return (0);
}

//export should not work wiht pipes
//export: `=h': not a valid identifier