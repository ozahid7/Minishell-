/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:26:06 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/16 17:40:17 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_name(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

t_env	*return_node(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*dup_name(char *src)
{
	int		i;
	int		len;
	char	*dst;

	dst = NULL;
	i = 0;
	len = 0;
	dst = malloc(sizeof(char) * ft_strlen(src));
	while (src[i] && src[i] != '=')
	{
		if (src[i] != '+')
			dst[len++] = src[i];
		i++;
	}
	dst[len] = '\0';
	return (dst);
}

char	*free_and(char *ptr)
{
	(void) ptr;
	free(ptr);
	return (NULL);
}

char	*check_plus(char *content)
{
	char	*ptr;

	if (check_char(content, '+'))
	{
		ptr = ft_strchr(content, '+');
		if (ptr[1] == '=')
		{
			ptr++;
			return (++ptr);
		}
	}
	return (0);
}
