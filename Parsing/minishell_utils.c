/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:28:33 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/19 20:15:37 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

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
				fprint(2, "Minishell: syntax error near unexpected token %c\n", q);
				g_exit_status = 258;
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

t_env	*after_while(int ac, char **av, char **env)
{
	t_env	*lst_env;

	(void) ac;
	(void) av;
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, SIG_IGN);
	lst_env = ft_remplire_env(env);
	return (lst_env);
}

void	ft_free(t_temp *lst_temp, t_list *lst)
{
	free_lst_temp(lst_temp);
	free_lst(lst);
}
