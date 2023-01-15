/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_temp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 00:09:14 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/15 14:40:49 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_temp	*ft_lstnew_temp(void *content, int q)
{
	t_temp	*newlst;

	newlst = (t_temp *) malloc(sizeof(t_temp));
	if (!newlst)
		return (NULL);
	newlst->content = content;
	newlst->i = q;
	newlst->fd = 0;
	newlst->red = NULL;
	newlst->next = NULL;
	return (newlst);
}

t_temp	*ft_lstlast_temp(t_temp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_temp(t_temp **alst, t_temp *new)
{
	t_temp	*lst;

	if (!*alst)
		*alst = new;
	else
	{
		lst = ft_lstlast_temp(*alst);
		lst->next = new;
	}
}

void	ft_lstadd_middle_temp(t_temp **alst, t_temp *new)
{
	t_temp	*lst;

	if (!*alst)
		*alst = new;
	else
	{
		lst = (*alst)->next;
		(*alst)->next = new;
		new->next = lst;
	}
}

void	ft_lstadd_front_temp(t_temp **alst, t_temp *new)
{
	new->next = *alst;
	*alst = new;
}
