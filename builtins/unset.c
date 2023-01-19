/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:16:01 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/19 13:12:45 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void prin(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s = %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

t_env	*del_node(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*target;

	if (!ft_strcmp((*env)->key, name))
	{
		target = *env;
		*env = (*env)->next;
		//env = &(target->next);
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
	//prin(*env);
	return (*env);
}

void	ft_unset(t_env **env, t_list *lst)
{
	char	*name;

	name = dup_name(lst->cmd[1]);
	if (env_len(*env) - 1 == 1)
	{
		if (!ft_strcmp((*env)->key, name))
		{
			free((*env)->key);
			free((*env)->value);
			*env = NULL;
			free(env);
		}
	}
	else
		*env = del_node(env, name);
	free(name);
}
