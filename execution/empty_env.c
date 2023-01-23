/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:26:08 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/23 16:51:53 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_exec(t_list *lst, t_env **env)
{
	int	fd[2];

	signal(SIGINT, SIG_IGN);
	ft_pipe(fd, lst, env);
	return (0);
}

t_env	*empty_env(t_env *lnv, t_env *new)
{
	new = ft_envnew(getcwd(NULL, 0), ft_strdup("PWD"));
	lst_addback_env(&lnv, new);
	new = ft_envnew(ft_strdup(PATH), ft_strdup("PATH"));
	lst_addback_env(&lnv, new);
	return (lnv);
}
