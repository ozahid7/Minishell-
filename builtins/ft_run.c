/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 00:20:46 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/21 11:15:06 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_run_utils(t_list *lst, t_env **env, int i)
{
	if (lst->cmd[1] == NULL)
		ft_exp(*env);
	while (lst->cmd[i])
	{
		if (ft_addnode(*env, lst->cmd[i++]))
			g_exit_status = 1;
	}
}

int	ft_run(t_list *lst, t_env **env)
{	
	int	i;

	i = 1;
	if (ft_strcmp(lst->cmd[0], "cd") == 0)
		ft_cd(*env, lst);
	else if (ft_strcmp(lst->cmd[0], "env") == 0)
		ftenv(*env);
	else if (ft_strcmp(lst->cmd[0], "echo") == 0)
		ft_echo(lst->cmd);
	else if (ft_strcmp(lst->cmd[0], "pwd") == 0)
		ft_pwd(lst);
	else if (!ft_strcmp(lst->cmd[0], "unset")
		&& lst->cmd[1] && check_name(*env, lst->cmd[1]))
		ft_unset(env, lst);
	else if (ft_strcmp(lst->cmd[0], "export") == 0)
		ft_run_utils(lst, env, i);
	else if (ft_strcmp(lst->cmd[0], "exit") == 0)
		f_exit(lst);
	return (0);
}
