/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:54:26 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/20 10:17:15 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_cond(t_list *lst, int *i, t_env *env)
{
	char	*str;

	if ((lst->cmd != NULL
			&& ft_strcmp(lst->cmd[0], "cd") == 0 && lst->cmd[1] == '\0')
		|| (ft_strcmp(lst->cmd[0], "cd") == 0
			&& ft_strcmp(lst->cmd[1], "~") == 0))
	{
		if (check_name(env, "HOME"))
			chdir("/Users/ozahid-");
		else
			fprint(2, "minishell: cd: HOME not set\n");
	}
	else if ((lst->cmd != NULL && ft_strcmp(lst->cmd[0], "cd") == 0 \
			&& ft_strcmp(lst->cmd[1], "-") == 0))
	{
		str = get_oldp(env);
		if (str != NULL)
		{
			fprint(1, "%s\n", str);
			chdir(str);
		}
		else
			fprint(2, "minishell: cd: OLDPWD not set\n");
		*i = 1;
	}
}

void	ft_cd(t_env *env, t_list *lst)
{
	int		i;
	char	*pwd;
	char	*old_pwd;
	char	*str;

	i = 0;
	pwd = NULL;
	str = NULL;
	old_pwd = getcwd(NULL, 0);
	cd_cond(lst, &i, env);
	if (lst->cmd[1] != NULL && chdir(lst->cmd[1]) == -1
		&& lst->cmd[1][0] != '-' && lst->cmd[1][0] != '~')
	{
		fprint(2, "minishell: cd: %s: No such file or directory\n",
			lst->cmd[1]);
		g_exit_status = 1;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	ft_change_pwd("PWD", pwd, env);
	if (i != 1)
		ft_change_pwd("OLDPWD", old_pwd, env);
	return ;
}

char	*ft_change_pwd(char *lst, char *pwd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcmp(env->key, lst) == 0)
			env->value = pwd;
		env = env->next;
	}
	env = tmp;
	return (0);
}

char	*get_oldp(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
			return (env->value);
		env = env->next;
	}
	env = tmp;
	return (NULL);
}
