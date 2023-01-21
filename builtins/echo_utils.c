/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:41:46 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/21 11:07:42 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_utils(char **content, int i, int j)
{
	while (content[i])
	{
		if (i != j)
			fprint(1, " ");
		fprint(1, "%s", content[i++]);
	}
	if (j == 1)
		ft_putstr_fd("\n", 1);
}

void	ft_echo(char **content)
{
	int	i;

	i = 1;
	if (!content[i])
		return (ft_putstr_fd("\n", 1));
	if (!ft_strcmp(content[i], "-n"))
		ft_echo_utils(content, 2, 2);
	else
		ft_echo_utils(content, 1, 1);
	g_exit_status = 0;
}
