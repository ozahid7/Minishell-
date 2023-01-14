/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:06:47 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/14 12:28:57 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

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
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_status = 1;
		rl_redisplay();
	}
}
