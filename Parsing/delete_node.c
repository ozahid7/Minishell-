/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:10:52 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/15 14:40:54 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_temp	*del_next_node(t_temp *node, int i)
{
	t_temp	*next;
	t_temp	*temp;
	t_temp	*del;

	temp = node;
	next = node->next->next;
	del = node->next;
	free(del->content);
	free(del);
	node->next = next;
	if (i == 0)
		return (temp);
	return (next);
}
