/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:20:35 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/16 16:38:21 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

void	ft_printexport(t_env *env)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	if (env->value || env->i)
		ft_putstr_fd("=\"", 1);
	ft_putstr_fd(env->value, 1);
	if (env->value || env->i)
		ft_putstr_fd("\"", 1);
	ft_putstr_fd("\n", 1);
}

void	ft_exp(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp_env;
	int		len;
	int		i;

	tmp = env;
	i = -1;
	len = env_len(env);
	while (++i < len)
	{
		env = tmp;
		tmp_env = env;
		while (env)
		{
			if ((ft_strcmp(tmp_env->key, env->key) > 0
					&& env->pos < 0)
				|| (tmp_env->pos >= 0 && env->pos < 0))
				tmp_env = env;
			env = env->next;
		}
		ft_printexport(tmp_env);
		tmp_env->pos = i;
	}
	env = tmp;
	reset_pos(env);
}

void	reset_pos(t_env *env)
{
	while (env)
	{
		env->pos = -1;
		env = env->next;
	}
}

int	check_char(char *content, char c)
{
	int		i;

	i = 0;
	while (content[i])
	{
		if (content[i] && content[i] == c)
			return (1);
		i++;
	}
	return (0);
}
