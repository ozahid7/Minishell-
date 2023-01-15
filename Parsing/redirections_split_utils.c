/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_split_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:27:39 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/15 14:41:31 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_temp	*ft_take_redirections_(t_temp *lst, t_red **red_t, int j, int *i)
{
	if (j == 0)
	{
		ft_lstadd_back_red(red_t, ft_lstnew_red(ft_strdup(lst->next->content), \
		ft_type_redirection(lst->content), 0));
		lst->red = *red_t;
		lst = del_next_node(lst, 0);
		free(lst->content);
		lst->content = ft_strdup("");
	}
	if (j == 1)
	{
		ft_lstadd_back_red(red_t, \
		ft_lstnew_red(ft_strdup(lst->next->next->content), \
		ft_type_redirection(lst->next->content), 0));
		lst->red = *red_t;
		lst = del_next_node(lst, 0);
		lst = del_next_node(lst, 0);
	}
	*i += 1;
	return (lst);
}

t_temp	*ft_join_lst_(t_temp *lst)
{
	t_temp	*tmp;

	tmp = lst;
	while (lst)
	{
		if ((ft_strcmp(lst->content, " ") != 0) \
		&& is_pipe_redirection(lst->content, lst->i) == 0)
			lst = ft_join_caracteres(lst);
		if (lst)
			lst = lst->next;
	}
	lst = tmp;
	delete_spaces_between(lst);
	between_pipe_redirections(lst);
	return (lst);
}
