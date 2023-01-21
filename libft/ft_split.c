/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 23:36:12 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/21 12:12:46 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_compteur(char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (s[i] && (s[i] == c))
		i++;
	while (s[i] != '\0')
	{
		j = i;
		while (s[j] && s[j] != c && s[j] != '\0')
		{
			j = ft_utils_split(s, j);
			i = j;
			if (s[j + 1] == c || s[j + 1] == '\0')
				k++;
			j++;
			i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (k);
}

char	**ft_freetab(char **p)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (p[len])
		len++;
	while (i <= len)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

static int	ft_iter(char const *s, int i, int j)
{
	if (s[j] == '\0')
	{
		i = j;
	}
	else
	{
		i = j + 1;
	}
	return (i);
}

static char	**ft_remp(char **p, char const *s, char c)
{
	int		i;
	int		j;
	int		tab;

	i = 0;
	tab = 0;
	while (s[i] && (s[i] == c))
		i++;
	while (*(s + i) != '\0')
	{
		j = i;
		while (s[j] != c && s[j] != '\0')
			j = (ft_utils_split(s, j) + 1);
		if (s[i] != c)
		{
			p[tab] = ft_substr(s, i, j - i);
			if (!p[tab])
				return (ft_freetab(p));
			tab++;
		}
		i = ft_iter(s, i, j);
	}
	p[tab] = NULL;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	p = (char **)malloc((ft_compteur(s, c) + 1) * sizeof(char *));
	if (!p)
	{
		free(p);
		return (NULL);
	}
	if (ft_remp(p, s, c) == NULL)
		return (NULL);
	return (p);
}
