/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:08:32 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/13 15:10:09 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

t_red	*ft_lstnew_red(void *content, int type, int fd)
{
	t_red	*newlst;

	newlst = (t_red *) malloc(sizeof(t_red));
	if (!newlst)
		return (NULL);
	newlst->file_name = content;
	newlst->type_redirection = type;
	newlst->fd = fd;
	newlst->next = NULL;
	return (newlst);
}

t_red	*ft_lstlast_red(t_red *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_red(t_red **alst, t_red *new)
{
	t_red	*lst;

	if (new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			lst = ft_lstlast_red(*alst);
			lst->next = new;
		}
	}
}

int	ft_type_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				return (HERDOC);
			return (INFILE);
		}
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				return (APPAND);
			return (OUTFILE);
		}
	}
	return (0);
}

void	ft_take_redirections(t_temp **lst, int i)
{
	t_red	*red;

	red = NULL;
	while ((*lst) && (*lst)->next)
	{
		if (is_pipe_redirection((*lst)->content, (*lst)->i) \
			&& ft_strcmp((*lst)->content, "|") != 0 && i == 0)
		{
			(*lst) = ft_take_redirections_((*lst), &red, 0, &i);
		}
		else if (is_pipe_redirection((*lst)->next->content, (*lst)->next->i) \
		&& ft_strcmp((*lst)->next->content, "|") != 0 \
		&& ft_strcmp((*lst)->content, "|") != 0)
		{
			if (!(*lst)->next->next)
				break ;
			(*lst) = ft_take_redirections_((*lst), &red, 1, &i);
		}
		else
		{
			red = NULL;
			i = 0;
			(*lst) = (*lst)->next;
		}
	}
}
