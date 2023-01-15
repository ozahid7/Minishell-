/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:33:35 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/15 15:25:44 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_out(t_red *red)
{
	int		fd;

	fd = open(red->file_name, O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		return (perror(""), 1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	ft_in(t_red	*red)
{
	int	fd;

	if (access(red->file_name, R_OK) == -1)
		return (perror(""), 1);
	else
	{
		fd = open(red->file_name, O_RDONLY, 0666);
		if (fd == -1)
			return (perror(""), 1);
		dup2(fd, 0);
		close(fd);
	}
	return (0);
}

int	ft_appand(t_red	*red)
{
	int	fd;

	fd = open(red->file_name, O_CREAT | O_RDWR | O_APPEND);
	if (fd == -1)
		return (perror(""), 1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	ft_execred(t_list *lst)
{
	if (lst->red)
	{
		if (lst->red->type_red == 11)
			return (ft_out(lst->red));
		if (lst->red->type_red == 10)
			return (ft_in(lst->red));
		if (lst->red->type_red == 13)
			return (ft_appand(lst->red));
	}
	return (0);
}
