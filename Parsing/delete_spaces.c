/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:43:52 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/17 23:34:21 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*delete_spaces(char *str)
{
	char	*s;
	int		i;
	int		len;

	i = 0;
	len = (ft_strlen(str) - 1);
	while (str[i] && str[i] == ' ')
		i++;
	while (len > i && str[len] == ' ')
		len--;
	s = ft_substr(str, i, (len - i) + 1);
	free(str);
	return (s);
}
