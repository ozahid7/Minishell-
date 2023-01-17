/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 01:56:02 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/17 17:04:01 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_env(char **env)
{
	t_env	*lnv;
	t_env	*new;
	char	**str;
	int		i;

	i = 1;
	new = NULL;
	lnv = NULL;
	if (!*env)
	{
		lnv = empty_env(lnv, new);
		return (lnv);
	}
	str = ft_split(env[0], '=');
	lnv = ft_envnew(str[1], str[0]);
	while (env[i])
	{
		str = ft_split(env[i], '=');
		new = ft_envnew(str[1], str[0]);
		lst_addback_env(&lnv, new);
		i++;
	}
	return (lnv);
}

char	*get_path(t_env *data)
{
	int		i;
	char	*str;

	i = 0;
	while (data)
	{
		if (data->key && ft_strcmp(data->key, "PATH") == 0)
		{
			str = data->value;
		}
		data = data->next;
	}
	return (str);
}

char	*path(t_env *data, char *cmd)
{
	char	**path;
	// t_env	*node;
	int		i;

	i = 0;
	data = return_node(data, "PATH");
	if (!data)
		return (printf("no such a file or directory\n"), cmd);
	path = ft_split(data->value, ':');
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
		if (!access (path[i], X_OK || F_OK))
			break ;
		i++;
	}
	if (access(path[i], X_OK || F_OK) != 0)
		fprint(2, "Minishell: %s: command not found\n", cmd);
	if (path[i] == NULL)
		return (cmd);
	return (path[i]);
}

int	ft_fork(t_pip p, t_env *env, t_list *cmd, int *fd)
{
	char	**arg;

	arg = get_arg(env);
	p.id = fork();
	if (p.id == -1)
		return (perror("fork"), 1);
	else if (p.id == 0)
	{
		ft_dup(fd, p.cout, p.pin);
		if (is_builtins(cmd))
			ft_run(cmd, &env);
		else
		{
		if (check_char(*cmd->cmd, '/') )
		{
			if (access(*cmd->cmd, X_OK || F_OK) == -1)
			{
				perror(*cmd->cmd);
				exit_with(127);
			}
			execve(*cmd->cmd, cmd->cmd, arg);
		}
			if (cmd->red && ft_execred(cmd) == 1)
				exit_with(1);
			execve(path(env, *cmd->cmd), cmd->cmd, arg);
			exit(0);
		}
		ft_freetab(arg);
		exit(0);
	}
	ft_freetab(arg);
	return (0);
}

int	ft_exec(t_list *lst, t_env **env)
{
	int	fd[2];

	get_path(*env);
	ft_pipe(fd, lst, *env);
	return (0);
}
