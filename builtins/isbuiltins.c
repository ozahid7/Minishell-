/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:06:46 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/17 19:00:07 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(t_list *lst)
{
	int		i;
	char	*str[7];

	i = 0;
	str[0] = "cd";
	str[1] = "pwd";
	str[2] = "echo";
	str[3] = "export";
	str[4] = "env";
	str[5] = "unset";
	str[6] = "exit";
	while (i < 7)
	{
		if (ft_strcmp(lst->cmd[0], str[i]) == 0)
		{
			if (lst->red)
			{
				ft_execred(lst);
				return (1);
			}
			return (1);
		}
		i++;
	}
	return (0);
}
