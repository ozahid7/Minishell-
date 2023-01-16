/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:04:41 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/16 16:50:08 by ozahid-          ###   ########.fr       */
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

void	ft_echo(char **content)
{
	int	i;

	i = 1;
	if (!content[i])
		return (ft_putstr_fd("\n", 1));
	if (!ft_strcmp(content[i], "-n"))
	{
		i = 2;
		while (content[i])
			fprint(1, "%s", content[i++]);
	}
	else
	{
		while (content[i])
			fprint(1, "%s", content[i++]);
		ft_putstr_fd("\n", 1);
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
