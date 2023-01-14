/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:33:06 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/14 10:44:17 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_temp	*lst_temp;
	t_list	*lst;
	t_env	*lst_env;
	char	*str;

	lst_env = after_while(ac, av, env);
	while (1)
	{
		str = readline("Minishell :$ ");
		if (!str)
			ft_exit();
		add_history(str);
		lst = NULL;
		lst_temp = NULL;
		if (ft_remplire_listes(str, &lst_temp, &lst_env) != -1)
		{
			lst = remplire_list(lst, &lst_temp);
		}	
		ft_free(lst_temp, lst);
	}
}
