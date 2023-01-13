/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 05:50:51 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/13 15:09:58 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	is_pipe_redirection(char *str, int i)
{
	if (((ft_strcmp(str, "|") == 0) || (ft_strcmp(str, "<") == 0) || \
		(ft_strcmp(str, "<<") == 0) || (ft_strcmp(str, ">") == 0) || \
		(ft_strcmp(str, ">>") == 0)) && (i == 0))
		return (1);
	return (0);
}

t_temp	*ft_join_caracteres(t_temp *lst)
{
	t_temp	*node_next;

	if (lst->next == NULL)
		return (lst);
	node_next = lst->next;
	while (node_next)
	{
		if ((ft_strcmp(node_next->content, " ") != 0) && \
			!is_pipe_redirection(node_next->content, lst->next->i))
		{
			lst->content = ft_strjoin(lst->content, node_next->content);
			if (node_next->i != 0)
				lst->i = node_next->i;
			node_next = del_next_node(lst, 1);
		}
		else
			break ;
	}
	lst = node_next;
	return (lst);
}

void	delete_pipe_spaces(t_temp *lst)
{
	t_temp	*before;
	t_temp	*after;
	int		i;
	int		j;

	i = 0;
	j = 0;
	before = lst;
	after = lst;
	while (lst)
	{
		if (ft_strcmp(lst->content, "|") == 0)
		{
			while (j < i)
			{
				before = before->next;
				j++;
			}
		}
		lst = lst->next;
		i++;
	}
}

void	delete_spaces_between(t_temp *lst)
{
	while (lst)
	{
		if ((ft_strcmp(lst->content, " ") == 0) && lst->i == 0)
		{
			while ((ft_strcmp(lst->next->content, " ") == 0) \
			&& lst->next->i == 0 && lst->next != NULL)
				lst = del_next_node(lst, 0);
		}
		lst = lst->next;
	}
}

void	ft_join_lst(t_temp **lst_t)
{
	t_temp	*lst;

	lst = *lst_t;
	while (lst)
	{
		if ((ft_strcmp(lst->content, " ") != 0) \
		&& is_pipe_redirection(lst->content, lst->i) == 0)
			lst = ft_join_caracteres(lst);
		if (lst)
			lst = lst->next;
	}
	lst = *lst_t;
	delete_spaces_between(lst);
	between_pipe_redirections(lst);
}
