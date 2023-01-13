/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:59:16 by ajafy             #+#    #+#             */
/*   Updated: 2021/11/19 02:38:26 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	size_t				i;

	p = s;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (p[i] == (unsigned char) c)
			return ((void *)s + i);
		i++;
	}
	if (c == '\0' && p[i] == '\0')
		return ((void *)(s + i));
	return (NULL);
}
