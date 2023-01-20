/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:06:47 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/20 19:53:24 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	handler_sig_herdoc(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		exit (1);
	}
	if (sig == 3)
	{
		printf("\b\b");
		return ;
	}
}

void	handler_sig(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = 1;
		rl_redisplay();
	}
}

void	handler_sig_(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
