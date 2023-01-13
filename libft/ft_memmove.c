/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:27:05 by ajafy             #+#    #+#             */
/*   Updated: 2021/11/18 23:42:02 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*psrc;
	char	*pdst;
	size_t	i;
	size_t	j;

	i = 0;
	psrc = (char *)src;
	pdst = (char *)dst;
	if (!pdst && !psrc)
		return (NULL);
	j = len;
	if (dst > src)
	{
		while (len)
		{
			len--;
			pdst[len] = psrc[len];
		}
	}
	while (i < len)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}
