/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 11:33:18 by ajafy             #+#    #+#             */
/*   Updated: 2021/11/29 09:02:14 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = NULL;
	if (*lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_lstdelone((*lst), del);
			*lst = temp;
		}
		free (*lst);
		lst = NULL;
	}
}
