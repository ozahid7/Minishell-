/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:26:08 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/23 02:26:33 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_env	*empty_env(t_env *lnv, t_env *new)
{
	new = ft_envnew(getcwd(NULL, 0), ft_strdup("PWD"));
	lst_addback_env(&lnv, new);
	new = ft_envnew(ft_strdup(PATH), ft_strdup("PATH"));
	lst_addback_env(&lnv, new);
	return (lnv);
}
