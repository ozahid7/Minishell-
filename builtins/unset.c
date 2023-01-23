/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:16:01 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/23 02:21:07 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*del_node(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*target;

	if (!ft_strcmp((*env)->key, name))
	{
		target = *env;
		*env = (*env)->next;
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

void	ft_unset(t_env **env, char *content)
{
	char	*name;

	name = dup_name(content);
	if (is_valid(name, content))
		fprint(2, "minishell: unset: %s"
			": not valid identifier\n", content);
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
		del_node(env, name);
	free(name);
}
