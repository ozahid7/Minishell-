/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:41:46 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/22 21:33:58 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_utils(char **content,  int j)
{
	int	i;

	i = 1;
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
	
	if (!content[1])
		return (ft_putstr_fd("\n", 1));
	if (!ft_strncmp(content[1], "-n", 3))
		ft_echo_utils(content, 2);
	else
		ft_echo_utils(content, 1);
	g_exit_status = 0;
}
