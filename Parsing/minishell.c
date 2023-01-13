/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:33:06 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/13 15:08:24 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	ft_exit(void)
{
	printf("\033[13C\033[1Aexit\n");
	exit (0);
}

int	ft_check_quotes(char *str)
{
	int		i;
	char	q;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i++];
			while (str[i] && str[i] != q)
				i++;
			if (str[i] == '\0')
			{
				write(2, "Erreur\n", 7);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_remplire_listes(char *s, t_temp **lst_t, t_env **lst_e)
{
	t_temp	*lst;

	if (ft_check_quotes(s) == -1)
		return (free(s), g_exit_status = 258, -1);
	*lst_t = ft_remplire_without_quotes(s);
	lst = *lst_t;
	if (redirections(lst, lst_e) == -1)
		return (-1);
	ft_expand(lst_e, lst_t);
	ft_join_lst(lst_t);
	if (check_operator_(*lst_t, 0, 0) == -1)
		return (write(2, "Erreur\n", 7), g_exit_status = 258, -1);
	ft_take_redirections(&lst, 0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_temp	*lst_temp;
	t_list	*lst;
	t_env	*lst_env;
	char	*str;

	(void) ac;
	(void) av;
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, SIG_IGN);
	lst_env = ft_remplire_env(env);
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
		free_lst_temp(lst_temp);
		free_lst(lst);
	}
}
