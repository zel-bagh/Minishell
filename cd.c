/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:03:21 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/28 19:47:29 by zel-bagh         ###   ########.fr       */
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

int   check_chdir_error(char *path)
{
    if (errno == 13)
        printf("minishell: cd: %s: Permission denied\n", path);
    if (errno == 20)
        printf("minishell: cd: %s: Not a directory\n", path);
    if (errno == 2)
        printf("minishell: cd: %s: No such file or directory\n", path);
    return (1);
}

char* get_actual_pwd(char **env, int *k)
{
    int i;
    int j;
    
    i = -1;
    *k = -1;
    while (env[++i])
    {
        j = compaire_arg_env(env[i], "PWD");
        if (j)
        *k = i;
        if (j == 2)
            return (env[i] + 4);
        if (j == 1)
            return (env[i] + 3);
    }
    return("");
}

void    change_oldpwd(char **env, char *tmp)
{
    int i;

    i = -1;
    while (env[++i])
        if (ft_compaire("OLDPWD", env[i]))
        {
            free (env[i]);
            env[i] = ft_strjoin("OLDPWD=", tmp);
        }
}

int	cd (char **args, char ***env)
{
	int			i;
    char        *tmp;
    char        pwd[256];

    errno = 0;
    if (chdir(args[0]))
        return (check_chdir_error(args[0]));
    tmp = get_actual_pwd(*env, &i);
    change_oldpwd(*env, tmp);
    if (i != -1)
    {
        free((*env)[i]);
        *env[i] = ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd)));
    }
    return (0);
}
