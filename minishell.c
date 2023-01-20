/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:33:06 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/20 22:22:05 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	exit_status(void)
{
	int	flag;
	int	pid;
	int	save;

	flag = 0;
	pid = waitpid(-1, &flag, 0);
	save = flag;
	while (pid != -1)
		pid = waitpid(-1, &flag, 0);
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, SIG_IGN);
	if (WIFSIGNALED(flag))
	{
		if (flag == 2)
			g_exit_status = 130;
		else if (flag == 3)
			g_exit_status = 131;
		else
			g_exit_status = 0;
	}
	else if (g_exit_status == 0)
		g_exit_status = flag / 256;
	else if (WEXITSTATUS(flag) != g_exit_status && g_exit_status == 0)
	{
		g_exit_status = WEXITSTATUS(flag);
		exit(g_exit_status);
	}
	if (flag == 13)
		g_exit_status = save / 256;
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
