/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 03:22:20 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/15 14:40:46 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_temp	*ft_split_redirections(t_temp **alst, int *i, char q)
{
	t_temp	*lst;
	char	*str;
	char	*s;

	lst = *alst;
	q = lst->content[(*i)++];
	if (lst->content[*i] == q)
	{
		s = ft_substr(lst->content, *i - 1, 2);
		(*i)++;
	}
	else
		s = ft_substr(lst->content, *i - 1, 1);
	str = ft_substr(lst->content, *i, (ft_strlen(lst->content) - *i));
	if (ft_strlen(str) > 0)
		ft_lstadd_middle_temp(&lst, ft_lstnew_temp(ft_strdup(str), 0));
	free(lst->content);
	lst->content = s;
	return (free(str), lst);
}

void	ft_check_redirections_(t_temp *lst)
{
	int		i;
	char	*tmp;

	i = 0;
	while (lst->content[i] != '\0')
	{
		if (lst->content[i] == '<' || lst->content[i] == '>')
		{
			if (i != 0)
			{
				ft_lstadd_middle_temp(&lst, \
				ft_lstnew_temp(ft_strdup(lst->content), 0));
				tmp = lst->content;
				lst->content = ft_substr(lst->content, 0, i);
				free(tmp);
				lst = lst->next;
			}
			lst = ft_split_redirections(&lst, &i, lst->content[i]);
			break ;
		}
		i++;
	}
}

void	ft_check_redirections(t_temp **lst_head)
{
	t_temp	*lst;

	lst = *lst_head;
	while (lst)
	{
		if (lst->i == 0)
			ft_check_redirections_(lst);
		lst = lst->next;
	}
}

void	between_pipe_redirections(t_temp *lst)
{
	while (lst)
	{
		if (lst->next)
		{
			if (ft_strcmp(lst->next->content, " ") == 0 && lst->next->i == 0)
			{
				if (is_pipe_redirection(lst->next->next->content, \
				lst->next->next->i))
					lst = del_next_node(lst, 0);
			}
		}
		if (is_pipe_redirection(lst->content, lst->i))
		{
			if (lst->next)
				if (ft_strcmp(lst->next->content, " ") == 0 \
				&& lst->next->i == 0)
					lst = del_next_node(lst, 0);
		}
		lst = lst->next;
	}
}
