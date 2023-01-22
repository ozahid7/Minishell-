/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:41:46 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/22 21:35:18 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_skip_n(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '-')
	{
		i++;
		while (content[i] && content[i] == 'n')
			i++;
		if (content[i] != '\0')
			return (0);
	}
	else
		return (0);
	return (1);
}

char	**ft_shift(char **content, int i)
{
	int	j;

	j = i + 1;
	while (content[j])
	{
		content[i++] = content[j++];
	}
	content[i] = NULL;
	return (content);
}

char	**skip_n(char **content)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (content[i])
	{
		if (ft_skip_n(content[i]))
		{
			if (j != 0)
				content = ft_shift(content, i);
			else
			{
				free(content[i]);
				content[i++] = ft_strdup("-n");
			}
			j++;
		}
		else
			return (content);
	}
	return (content);
}

void	ft_echo_utils(char **content, int j)
{
	int	i;

	i = j;
	while (content[i])
	{
		if (i > j)
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
	content = skip_n(content);
	if (!ft_strcmp(content[1], "-n"))
		ft_echo_utils(content, 2);
	else
		ft_echo_utils(content, 1);
	g_exit_status = 0;
}
