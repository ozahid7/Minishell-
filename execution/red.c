/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 01:42:10 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/24 00:05:22 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_out(t_red *red)
{
	int	fd;

	fd = open(red->file_name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		return (perror(""), 1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	ft_in(t_red	*red)
{
	int	fd;

	fd = open(red->file_name, O_RDONLY, 0777);
	if (fd == -1)
		return (perror(""), 1);
	if (access(red->file_name, R_OK) == -1)
		return (perror(""), 1);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	ft_apnd(t_red *red)
{
	int		fd;

	fd = open(red->file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
		return (perror(""), 1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	ft_hrdc(t_red *red)
{
	t_red	*tmp;

	tmp = ft_lstlast_red(red);
	dup2(tmp->fd, 0);
	close(tmp->fd);
	return (0);
}

int	ft_execred(t_list *lst)
{
	if (lst->red)
	{
		if (lst->red->type_red == 7)
			return (ft_out(lst->red));
		if (lst->red->type_red == 4)
			return (ft_in(lst->red));
		if (lst->red->type_red == 44)
			return (ft_hrdc(lst->red));
		if (lst->red->type_red == 77)
			return (ft_apnd(lst->red));
	}
	return (1);
}
