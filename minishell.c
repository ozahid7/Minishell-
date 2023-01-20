/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:33:06 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/20 15:06:37 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	exit_status(void)
{
	int	flag;
	int	pid;

	flag = 0;
	pid = waitpid(-1, &flag, 0);
	while (pid != -1)
		pid = waitpid(-1, &flag, 0);
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, SIG_IGN);
	if (flag != -1)
		g_exit_status = flag / 256;
	if (WEXITSTATUS(flag) != g_exit_status)
	{
		g_exit_status = WEXITSTATUS(flag);
		exit(g_exit_status);
	}	
}

int	main(int ac, char **av, char **env)
{
	t_temp	*lst_temp;
	t_list	*lst;
	t_env	*lst_env;
	char	*str;

	lst_env = before_while(ac, av, env);
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
			ft_exec(lst, &lst_env);
			exit_status();
			ft_free(lst_temp, lst);
		}
	}
}
