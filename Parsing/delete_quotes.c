/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 23:10:07 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/13 15:09:35 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	is_space_pipe(char c)
{
	if (c == '|' || c == ' ')
		return (1);
	return (0);
}

int	is_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	delete_quotes(char *str, int i, int *q, char **s)
{
	char	c;
	int		j;

	if (str[i] == '\'')
		*q = 1;
	else
		*q = 2;
	c = str[i++];
	j = i;
	while (str[i] && str[i] != c)
		i++;
	*s = ft_substr(str, j, i - j);
	return (i);
}

int	remp_string(char *str, int i, char **s)
{
	int	j;

	j = i;
	while (str[i + 1] && str[i + 1] != '\'' && str[i + 1] != '\"' \
		&& str[i + 1] != ' ' && str[i + 1] != '|')
		i++;
	*s = ft_substr(str, j, (i - j) + 1);
	return (i);
}

t_temp	*ft_remplire_without_quotes(char *str)
{
	t_temp	*lst;
	int		i;
	int		q;
	char	*s;
	char	*c;

	i = 0;
	lst = NULL;
	str = delete_spaces(str);
	while (str[i])
	{
		q = 0;
		c = ft_substr(str, i, 1);
		if (is_space_pipe(str[i]))
			s = ft_strdup(c);
		else if (is_quotes(str[i]))
			i = delete_quotes(str, i, &q, &s);
		else
			i = remp_string(str, i, &s);
		ft_lstadd_back_temp(&lst, ft_lstnew_temp(s, q));
		i++;
		free(c);
	}
	ft_check_redirections(&lst);
	return (free(str), lst);
}
