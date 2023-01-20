/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:33:35 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/20 22:21:37 by ozahid-          ###   ########.fr       */
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

	fd = open(red->file_name, O_RDONLY, 0666);
	if (fd == -1)
		return (perror(""), 1);
	if (access(red->file_name, R_OK) == -1)
		return (perror(""), 1);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	ft_apnd_hrdc(t_red	*red)
{
	int		fd;
	t_red	*tmp;

	tmp = ft_lstlast_red(red);
	if (red->type_red == 77)
	{
		fd = open(red->file_name, O_CREAT | O_RDWR | O_APPEND);
		if (fd == -1)
			return (perror(""), 1);
		dup2(fd, 1);
		close(fd);
	}
	else if (red->type_red == 44)
	{
		dup2(tmp->fd, 0);
		close(tmp->fd);
	}
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
		if (lst->red->type_red == 77 || lst->red->type_red == 44)
			return (ft_apnd_hrdc(lst->red));
	}
	return (0);
}

t_env	*empty_env(t_env *lnv, t_env *new)
{
	new = ft_envnew(getcwd(NULL, 0), ft_strdup("PWD"));
	lst_addback_env(&lnv, new);
	new = ft_envnew(ft_strdup(PATH), ft_strdup("PATH"));
	lst_addback_env(&lnv, new);
	return (lnv);
}
