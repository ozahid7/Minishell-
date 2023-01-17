/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:16:01 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/16 23:30:43 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if(t_env *env, char *name, int *i)
{
	while (env)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (1);
		env = env->next;
		*i = *i + 1;
	}
	return (0);
}

t_env	*del_node(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*target;

	if (!ft_strcmp((*env)->key, name))
	{
		target = *env;
		*env = target->next;
	}
	else
	{
		tmp = *env;
		while (tmp->next && ft_strcmp(tmp->next->key, name))
			tmp = tmp->next;
		if (!tmp->next)
			return (NULL);
		target = tmp->next;
		tmp->next = target->next;
	}
	ft_envdelone(target, free);
	return (*env);
}

void	ft_unset(t_env **env, t_list *lst)
{
	char	*name;

	name = dup_name(lst->cmd[1]);
	del_node(env, name);
	free(name);
}
