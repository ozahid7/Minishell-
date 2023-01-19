/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:31:27 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/19 20:27:48 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_check_(char *str, char *strn)
{
	if (ft_strcmp(str, strn) == 0)
		return (-1);
	if (is_pipe_redirection(strn, 0) && ft_strcmp(str, "|") != 0)
		return (-1);
	if ((ft_strcmp(str, "|") != 0) && \
	(ft_strcmp(strn, "|") == 0))
		return (-1);
	return (0);
}

int	check_operator_(t_temp *lst, int p, int i)
{
	int	len;

	len = ft_lstsize_temp(lst);
	while (lst)
	{
		if (is_pipe_redirection(lst->content, lst->i))
		{
			if (i == 0)
				if (ft_strcmp(lst->content, "|") == 0 && p > 1)
					return (-1);
			if (i == len - 1)
				return (-1);
			if (lst->next->i == 0)
				if (ft_check_(lst->content, lst->next->content) == -1)
					return (-1);
		}
		i++;
		if ((ft_strcmp(lst->content, "|") == 0))
			p = 0;
		else
			p++;
		lst = lst->next;
	}
	return (0);
}

int	check_op_bfr_herdoc(t_temp *lst, int i)
{
	int		len;

	len = ft_lstsize_temp(lst);
	while (lst)
	{
		if (is_pipe_redirection(lst->content, lst->i))
		{
			if ((ft_strcmp(lst->content, "<<") == 0) && (lst->i == 0))
				return (1);
			if (i == 0)
				if (ft_strcmp(lst->content, "|") == 0)
					return (-1);
			if (i == len - 1)
				return (-1);
			if (lst->next->i == 0)
				if (ft_check_(lst->content, lst->next->content) == -1)
					return (-1);
		}
		i++;
		if ((ft_strcmp(lst->content, "|") == 0))
			i = 0;
		lst = lst->next;
	}
	return (0);
}

int	ft_valide_herdoc(t_temp *lst)
{
	while (lst)
	{
		if ((ft_strcmp(lst->content, "<<") == 0) && (lst->i == 0))
		{
			if (lst->next)
			{
				if (is_pipe_redirection(lst->next->content, lst->next->i) == 0)
					return (1);
				else
					return (0);
			}
			else
				return (0);
		}
		lst = lst->next;
	}
	return (0);
}

int	is_herdoc(t_temp *lst)
{
	if (lst)
	{
		if ((ft_strcmp(lst->content, "<<") == 0) && (lst->i == 0))
		{
			if (lst->next)
			{
				if (is_pipe_redirection(lst->next->content, lst->next->i) == 0)
					return (1);
				else
					return (0);
			}
			else
				return (0);
		}
	}
	return (0);
}
