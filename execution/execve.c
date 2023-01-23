/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 01:56:02 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/23 16:57:42 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_utils(char **path, t_env *data, char *cmd, char *ret)
{
	int	i;

	i = 0;
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

char	*path(t_env *data, char *cmd)
{
	char	**path;
	char	*ret;

	path = NULL;
	ret = cmd;
	if (check_char(ret, '/') && access(ret, X_OK || F_OK) != 0)
	{
		fprint(2, "minishell: cd: %s: No such file or directory\n",
			ret, 0);
		return (0);
	}
	data = return_node(data, "PATH");
	if (!data)
		return (cmd);
	if (access(cmd, X_OK || F_OK) == 0)
		return (cmd);
	if (data->value)
		ret = path_utils(path, data, cmd, ret);
	return (ret);
}

int	exec_cmd(t_list *cmd, char *path, char **arg)
{
	if (cmd->red && ft_execred(cmd) == 1)
		exit(1);
	if (cmd->red && !ft_strcmp(cmd->cmd[0], ""))
		return (1);
	if (execve(path, cmd->cmd, arg) == -1)
		return (fprint(2, "Minishell: %s: command not found\n", \
		cmd->cmd[0]), exit(127), 0);
	return (1);
}

char	**fork_utils(char **arg, t_env *env, int *fd, t_pip *p)
{
	arg = get_arg(env);
	handler_sig_();
	ft_dup(fd, p->cout, p->pin);
	return (arg);
}

int	ft_fork(t_pip p, t_env *env, t_list *cmd, int *fd)
{
	char	**arg;
	char	*pat;

	arg = NULL;
	pat = path(env, *cmd->cmd);
	if (pat)
	{
		p.id = fork();
		if (p.id == -1)
			return (perror("fork"), 1);
		else if (p.id == 0)
		{
			arg = fork_utils(arg, env, fd, &p);
			if (pat && is_builtins(cmd))
				ft_run(cmd, &env);
			else
				if (exec_cmd(cmd, pat, arg) == 0)
					return (0);
			exit (0);
		}
		if (ft_strcmp(pat, cmd->cmd[0]) && !access(pat, X_OK))
			free(pat);
	}
	return (0);
}
