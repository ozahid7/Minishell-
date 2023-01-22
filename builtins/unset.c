/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:16:01 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/22 19:44:51 by ozahid-          ###   ########.fr       */
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

void	ft_unset(t_env **env, t_list *lst)
{
	char	*name;

	name = dup_name(lst->cmd[1]);
	if (is_valid(name, lst->cmd[1])) 
		fprint(2, "minishell: unset: %s"
			": not valid identifier\n", lst->cmd[1]);
	else if (env_len(*env) - 1 == 1)
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
