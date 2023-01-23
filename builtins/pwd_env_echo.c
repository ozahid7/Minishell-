/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:04:41 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/23 02:20:01 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ftenv(t_env *env)
{	
	while (env)
	{
		if (env->value != NULL)
			fprint(1, "%s=%s \n", env->key, env->value);
		else if (env->i)
			fprint(1, "%s=\n", env->key);
		env = env->next;
	}
}

void	ft_pwd(t_list *lst)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		fprint(2, "minishell: pwd: No such file or directory\n");
		return ;
	}
	if (lst->cmd != NULL && ft_strcmp(lst->cmd[0], "pwd") == 0)
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
}

int	check_for_exit(char *str, int *j)
{
	int	i;

	i = 0;
	*j = 0;
	if (!str)
		return (0);
	while (str[i] == '+' || str[i] == '-')
	{
		*j = *j + 1;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	f_exit(t_list *cmd)
{
	int	i;

	fprint(2, "exit\n");
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		fprint(2, "Minishell: exit: too many arguments\n");
		g_exit_status = 1;
	}
	else
	{
		if (cmd->cmd[1])
		{
			if (check_for_exit(cmd->cmd[1], &i))
			{
				if (i != 1)
					fprint(2, "Minishell: %s: %s: numeric argument required\n", \
				cmd->cmd[0], cmd->cmd[1]);
				g_exit_status = 255;
			}
			else
				exit(ft_atoi(cmd->cmd[1]));
		}
		exit(g_exit_status);
	}
}
