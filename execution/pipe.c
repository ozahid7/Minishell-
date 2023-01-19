/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 03:09:55 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/19 13:53:35 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup(int *fd, int c, int p)
{
	dup2(p, 0);
	dup2(c, 1);
	close(fd[0]);
	close (p);
	close (c);
}

static int	is_built(t_list *lst)
{
	if ((!ft_strcmp(lst->cmd[0], "export") && lst->cmd[1])
		|| !ft_strcmp(lst->cmd[0], "cd")
		|| !ft_strcmp(lst->cmd[0], "unset"))
		return (1);
	return (0);
}

void	ft_pipe(int *fd, t_list *lst, t_env **head_env)
{
	t_pip	p;
	t_env	*env;

	p.pin = -1;
	p.save = -1;
	fd[1] = -1;
	env = *head_env;
	while (lst)
	{
		p.cout = -1;
		if (lst->next)
		{
			if (pipe(fd) == -1)
				return (perror("pipe"));
			p.cout = fd[1];
			p.save = fd[0];
		}
		if (*lst->cmd && is_built(lst))
			ft_run(lst, head_env);
		else
			ft_fork(p, env, lst, fd);
		close(fd[1]);
		close(p.pin);
		lst = lst->next;
		p.pin = p.save;
	}
	close(p.save);
}
