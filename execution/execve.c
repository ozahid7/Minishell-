/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 01:56:02 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/20 10:46:28 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(t_env *data)
{
	int		i;
	char	*str;

	i = 0;
	while (data)
	{
		if (ft_strcmp(data->key, "PATH") == 0)
			str = data->value;
		data = data->next;
	}
	return (str);
}

char	*path(t_env *data, char *cmd)
{
	char	**path;
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
		return (cmd);
	return (path[i]);
}

int	ft_fork(t_pip p, t_env *env, t_list *cmd, int *fd)
{
	char	**arg;
	char	*pat;

	pat = path(env, *cmd->cmd);
	arg = get_arg(env);
	p.id = fork();
	if (p.id == -1)
		return (perror("fork"), 1);
	else if (p.id == 0)
	{
		ft_dup(fd, p.cout, p.pin);
		if (pat && is_builtins(cmd))
			ft_run(cmd, &env);
		else
		{
			if (cmd->red && ft_execred(cmd) == 1)
				exit_with(1);
			if (execve(pat, cmd->cmd, arg) == -1)
				return (fprint(2, "Minishell: %s: command not found\n", \
				cmd->cmd[0]), exit(127), 0);
		}
		exit (0);
	}
	return (ft_freetab(arg), 0);
}

int	ft_exec(t_list *lst, t_env **env)
{
	int	fd[2];

	ft_pipe(fd, lst, env);
	return (0);
}
