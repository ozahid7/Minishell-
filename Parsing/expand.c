/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 00:14:19 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/20 10:08:03 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char) s1[i] == (unsigned char) s2[i])
			i++;
		else if ((unsigned char) s1[i] > (unsigned char) s2[i])
			return (1);
		else
			return (-1);
	}
	return (0);
}

char	*ft_replace_dollar(char *str, int *d, char *chaine, t_env *env)
{
	int		i;
	int		start;
	char	*key;

	i = *d + 1;
	start = i;
	while (str[i] && ((ft_isalnum((int)str[i]) == 1) || str[i] == '_'))
		i++;
	key = ft_substr(str, start, i - start);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			chaine = ft_strjoin(chaine, env->value);
		env = env->next;
	}
	*d = i;
	if (start == i)
	{
		if (str[i] == '?')
			chaine = ft_strjoin_(chaine, ft_itoa(g_exit_status));
		else
			chaine = ft_strjoin(chaine, "$");
	}
	return (free(key), *d += (str[i] == '?'), chaine);
}

char	*dollar(char *str, t_env **lst_e)
{
	int		i;
	int		start;
	int		q;
	char	*s;

	i = 0;
	q = 0;
	start = 0;
	s = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			s = ft_strjoin_(s, ft_substr(str, start, i - start));
			start = i;
			s = ft_replace_dollar(str, &start, s, *lst_e);
		}
		i++;
	}
	s = ft_strjoin_(s, ft_substr(str, start, i - start));
	free(str);
	return (s);
}

void	ft_expand(t_env **lst_e, t_temp **lst_t)
{
	t_temp	*lst;
	int		j;

	lst = *lst_t;
	while (lst)
	{
		if (lst->i != 1)
		{
			j = 0;
			while (lst->content[j])
			{
				if (lst->content[j] == '$')
					lst->content = dollar(lst->content, lst_e);
				j++;
			}
		}
		lst = lst->next;
	}
}
