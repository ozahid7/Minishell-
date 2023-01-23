/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:08:56 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/23 23:33:54 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	herdoc(t_temp *lst, int *fds, t_env **head_env, int i)
{
	char	*str;

	str = NULL;
	while (1)
	{	
		str = readline("> ");
		if (!str)
		{
			fprint (1, "\b\b");
			break ;
		}	
		if (ft_strcmp(str, lst->next->content) == 0)
			break ;
		while (str[i])
		{
			if (str[i] == '$')
				str = dollar(str, head_env);
			i++;
		}
		ft_putendl_fd(str, fds[1]);
		write(fds[1], "\0", 1);
	}
}

int	ft_valide_red(t_temp *lst, int i, int len)
{
	if (ft_strcmp(lst->content, "<<") == 0)
		if (ft_valide_herdoc(lst))
			return (-2);
	if (i == 0)
		if (ft_strcmp(lst->content, "|") == 0)
			return (-1);
	if (i == len - 1)
		return (-1);
	if (lst->next->i == 0)
		if (ft_check_(lst->content, lst->next->content) == -1)
			return (-1);
	return (0);
}

void	herdoc_in(t_temp **lst, int *fds, t_env **head_env)
{
	signal (SIGINT, handler_sig_herdoc);
	(*lst) = ft_join_lst_(*lst);
	if (check_op_bfr_herdoc(*lst, 0) != 1)
		exit (0);
	if (ft_valide_herdoc(*lst) == 0)
		exit (0);
	herdoc(*lst, fds, head_env, 0);
	close(fds[1]);
	exit (0);
}

int	redirections(t_temp *lst, t_env **head_env)
{
	int		id;
	int		fds[2];

	while (lst)
	{
		if (is_herdoc(lst))
		{
			if (pipe(fds))
				exit (0);
			lst->fd = fds[0];
			signal(SIGINT, SIG_IGN);
			id = fork();
			if (id == 0)
				herdoc_in(&lst, fds, head_env);
			wait(&id);
			signal(SIGINT, handler_sig);
			if (id != 0)
				return (g_exit_status = 1, -1);
			close(fds[1]);
		}
		lst = lst->next;
	}
	return (0);
}

t_list	*remplire_list(t_list *lst, t_temp **head_temp)
{
	t_temp	*lst_temp;

	lst_temp = *head_temp;
	lst = ft_split_list(lst, lst_temp);
	return (lst);
}
