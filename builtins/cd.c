/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:54:26 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/23 17:19:04 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_home(t_env *env)
{
	t_env	*home;

	home = return_node(env, "HOME");
	if (check_name(env, "HOME"))
		chdir(home->value);
	else
		fprint(2, "minishell: cd: HOME not set\n");
}

void	cd_cond2(t_list *lst, int *i, t_env *env)
{
	t_env	*old;

	g_exit_status = 0;
	if ((lst->cmd != NULL
			&& ft_strcmp(lst->cmd[0], "cd") == 0 && lst->cmd[1] == '\0')
		|| (ft_strcmp(lst->cmd[0], "cd") == 0
			&& ft_strcmp(lst->cmd[1], "~") == 0))
		cd_home(env);
	else if ((lst->cmd != NULL && ft_strcmp(lst->cmd[0], "cd") == 0 \
			&& ft_strcmp(lst->cmd[1], "-") == 0))
	{
		old = return_node(env, "OLDPWD");
		if (old)
		{
			if (check_name(env, old->key))
				fprint(1, "%s\n", old->value);
			if (check_name(env, old->key))
				chdir(old->value);
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

	i = 0;
	pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	cd_cond2(lst, &i, env);
	if (lst->cmd[1] != NULL && chdir(lst->cmd[1]) == -1
		&& lst->cmd[1][0] != '-' && lst->cmd[1][0] != '~')
	{
		fprint(2, "minishell: cd: %s: No such file or directory\n",
			lst->cmd[1]);
		g_exit_status = 1;
		free (old_pwd);
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_change_pwd("PWD", pwd, env);
	if (old_pwd && i != 1)
		ft_change_pwd("OLDPWD", old_pwd, env);
	free(pwd);
	free(old_pwd);
}

char	*ft_change_pwd(char *str, char *pwd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			free(env->value);
				env->value = ft_strdup(pwd);
		}
		env = env->next;
	}
	env = tmp;
	return (0);
}
