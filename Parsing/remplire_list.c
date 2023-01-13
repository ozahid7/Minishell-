/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplire_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:42:02 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/13 15:10:24 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	is_pipe(char *str, int i)
{
	if ((ft_strcmp(str, "|") == 0) && (i == 0))
		return (1);
	return (0);
}

int	ft_lstsize_pipe(t_temp *lst)
{
	int	i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		if (is_pipe(lst->content, lst->i))
			i++;
		lst = (t_temp *) lst->next;
	}
	return (i);
}

char	**ft_split_list_utils(t_temp *lst, int len, t_red **head)
{
	char	**s;
	int		i;

	i = 0;
	s = malloc(len * sizeof(char *) + 1);
	if (!s)
		return (NULL);
	while (i < len && lst)
	{
		if (ft_strcmp(lst->content, " ") != 0)
		{
			s[i++] = lst->content;
			if (lst->red)
				ft_lstadd_back_red(head, lst->red);
		}
		lst = lst->next;
	}
	s[i] = NULL;
	if (i == 0)
		return (NULL);
	return (s);
}

t_list	*ft_split_list(t_list *lst, t_temp *lst_temp)
{
	int		i;
	int		k;
	t_temp	*temp;
	t_red	*red;
	char	**cmd;

	i = 0;
	cmd = NULL;
	while (lst_temp)
	{
		k = 0;
		temp = lst_temp;
		while (lst_temp && (is_pipe(lst_temp->content, lst_temp->i) == 0))
		{
			if (ft_strcmp(lst_temp->content, " ") != 0)
				k++;
			lst_temp = lst_temp->next;
		}
		red = NULL;
		cmd = ft_split_list_utils(temp, k, &red);
		ft_lstadd_back(&lst, ft_lstnew(cmd, red));
		if (lst_temp)
			lst_temp = lst_temp->next;
	}
	return (lst);
}

t_list	*remplire_list(t_list *lst, t_temp **head_temp)
{
	t_temp	*lst_temp;

	lst_temp = *head_temp;
	lst = ft_split_list(lst, lst_temp);
	return (lst);
}
