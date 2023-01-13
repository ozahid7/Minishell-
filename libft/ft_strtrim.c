/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:23:14 by ajafy             #+#    #+#             */
/*   Updated: 2021/11/21 04:47:06 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_prefixe(char const *s, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && set[j])
	{
		if (s[i] != set[j])
			j++;
		else
		{
			i++;
			j = 0;
		}
	}
	return (i);
}

static int	ft_suffixe(char const *s1, char const *set, int i)
{
	int	len;
	int	j;

	j = 0;
	len = ft_strlen(s1);
	len--;
	while (len > i && set[j])
	{
		if (s1[len] != set[j])
			j++;
		else
		{
			len--;
			j = 0;
		}
	}
	return (len);
}

static char	*ft_remplir(char *str, char const *s1, int len, int i)
{
	int	j;

	j = 0;
	while (i <= len)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	i = ft_prefixe(s1, set);
	len = ft_suffixe(s1, set, i);
	str = malloc (len - i + 2);
	if (!str)
		return (NULL);
	str = ft_remplir(str, s1, len, i);
	return (str);
}
