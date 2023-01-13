/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 01:58:00 by ajafy             #+#    #+#             */
/*   Updated: 2021/11/22 23:11:51 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static char	*ft_allouer(char *p, int n, int i)
{
	if (n <= 0)
		p = (char *)malloc(i + 2);
	else
		p = (char *)malloc(i + 1);
	return (p);
}

static int	ft_count( long x)
{
	int	i;

	i = 0;
	if (x < 0)
		x *= (-1);
	while (x > 0)
	{
		x /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;
	long	x;

	p = NULL;
	x = n;
	i = ft_count(x);
	p = ft_allouer(p, n, i);
	if (!p)
		return (NULL);
	if (x < 0)
	{
		p[0] = '-';
		x *= (-1);
		i++;
	}
	if (n == 0)
		p[i++] = 0 + 48;
	p[i] = '\0';
	while (x > 0)
	{
		p[--i] = (x % 10) + 48;
		x /= 10;
	}
	return (p);
}
