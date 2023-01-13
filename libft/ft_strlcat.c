/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:54:28 by ajafy             #+#    #+#             */
/*   Updated: 2021/11/19 21:45:40 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	r;
	size_t	i;
	size_t	res;

	r = ft_strlen(dst);
	i = 0;
	if (dstsize > r)
		res = ft_strlen(src) + r;
	else
		res = ft_strlen(src) + dstsize;
	if (r < dstsize - 1 && dstsize != 0)
	{
		while (src[i] && r < dstsize - 1)
		{
			dst[r] = src[i];
			r++;
			i++;
		}
		dst[r] = '\0';
	}
	return (res);
}
