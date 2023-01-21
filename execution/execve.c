/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 01:56:02 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/22 00:26:39 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path(t_env *data, char *cmd)
{
	char	**path;
	char	*ret;
	int		i;

	i = 0;
	data = return_node(data, "PATH");
	if (!data)
		return (cmd);
	if (check_char(cmd, '/') || access(cmd, X_OK || F_OK) == 0)
		return (cmd);
	path = ft_split(data->value, ':');
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
		if (!access (path[i], X_OK || F_OK))
			break ;
		i++;
	}
	if (path[i] == NULL)
		return (ft_freetab(path), cmd);
	ret = ft_strdup(path[i]);
	ft_freetab(path);
	return (ret);
}

int	exec_cmd(t_list *cmd, char *path, char **arg)
{
	if (cmd->red && ft_execred(cmd) == 1)
		exit(1);
	if (execve(path, cmd->cmd, arg) == -1)
		return (fprint(2, "Minishell: %s: command not found\n", \
		cmd->cmd[0]), exit(127), 0);
	return (1);
}

int	ft_fork(t_pip p, t_env *env, t_list *cmd, int *fd)
{
	char	**arg;
	char	*pat;

	arg = NULL;
	pat = path(env, *cmd->cmd);
	p.id = fork();
	if (p.id == -1)
		return (perror("fork"), 1);
	else if (p.id == 0)
	{
		arg = get_arg(env);
		handler_sig_();
		ft_dup(fd, p.cout, p.pin);
		if (pat && is_builtins(cmd))
			ft_run(cmd, &env);
		else
			if (exec_cmd(cmd, pat, arg) == 0)
				return (0);
	}
	if (ft_strcmp(pat, cmd->cmd[0]) && !access(pat, X_OK))
		free(pat);
	return (0);
}

int	ft_exec(t_list *lst, t_env **env)
{
	int	fd[2];

	signal(SIGINT, SIG_IGN);
	ft_pipe(fd, lst, env);
	return (0);
}
