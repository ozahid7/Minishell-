/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:32:59 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/23 19:52:57 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<fcntl.h>
# include<curses.h>
# include<stdlib.h>
# include<unistd.h>
# include<stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "printf_/ft_printf.h"

# define INFILE 4
# define OUTFILE 7
# define HERDOC 44
# define APPAND 77
# define PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"

int	g_exit_status;

typedef struct s_pip
{
	int	save;
	int	cout;
	int	pin;
	int	id;
}	t_pip;

/*
	Redirections_list
*/
void	exit_with(int nb);
t_red	*ft_lstnew_red(void *content, int type, int fd);
t_red	*ft_lstlast_red(t_red *lst);
void	ft_lstadd_back_red(t_red **alst, t_red *new);
int		ft_type_redirection(char *str);
/*
	Temp_list
*/

typedef struct s_temp
{
	char			*content;
	int				i;
	int				fd;
	t_red			*red;
	struct s_temp	*next;
}	t_temp;

void	ft_lstadd_front_temp(t_temp **alst, t_temp *new);
void	ft_lstadd_middle_temp(t_temp **alst, t_temp *new);
t_temp	*del_next_node(t_temp *node, int i);
t_temp	*ft_lstnew_temp(void *content, int q);
int		ft_lstsize_temp(t_temp *lst);
t_temp	*ft_lstlast_temp(t_temp *lst);
void	ft_lstadd_back_temp(t_temp **alst, t_temp *new);
t_temp	*ft_remplire_without_quotes(char *str);
int		check_operator(t_temp *lst);
void	between_pipe_redirections(t_temp *lst);
int		remp_string(char *str, int i, char **s);
int		delete_quotes(char *str, int i, int *q, char **s);
int		is_pipe_redirection(char *str, int i);
int		is_space_pipe(char c);
int		is_quotes(char c);
t_temp	*ft_join_caracteres(t_temp *lst);
void	delete_pipe_spaces(t_temp *lst);
void	delete_spaces_between(t_temp *lst);

/*
	Env_list
*/

typedef struct s_env
{
	char			*key;
	char			*value;
	int				pos;
	int				i;
	struct s_env	*next;
}	t_env;

void	prin(t_env *env);
t_list	*ft_remplire_list(char **tab);
t_env	*lstnew_env(char **content);
t_env	*ft_remplire_env(char **content);
t_env	*lstlast_env(t_env *lst);
void	lst_addback_env(t_env **head, t_env *new);

void	ft_expand(t_env **lst_e, t_temp **lst_t);
void	ft_join_lst(t_temp **lst_t);
char	*delete_spaces(char *str);
void	ft_check_redirections(t_temp **lst_head);

void	ft_take_redirections(t_temp **lst_t, int i);
t_temp	*ft_take_redirections_(t_temp *lst, t_red **red_t, int j, int *i);
t_list	*remplire_list(t_list *lst, t_temp **head_temp);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_path(char const *s1, char const *s2);
char	**ft_delete_quotes(char **str);

/*
Redirections
*/

int		redirections(t_temp *lst, t_env **head_env);
char	*dollar(char *str, t_env **lst_e);
int		check_operator_(t_temp *lst, int p, int i);
int		check_herdoc_(t_temp **head_temp);
int		ft_valide_red(t_temp *lst, int i, int len);
int		ft_valide_herdoc(t_temp *lst);
int		check_operator_herdoc(t_temp *lst, t_env **head_env, int *fds);
int		ft_check_(char *str, char *strn);
int		check_operator_pipe(t_temp *lst);
void	herdoc(t_temp *lst, int *fds, t_env **head_env, int i);
int		check_op_bfr_herdoc(t_temp *lst, int i);
int		is_herdoc(t_temp *lst);
t_temp	*ft_join_lst_(t_temp *lst);
void	herdoc_in(t_temp **lst, int *fds, t_env **head_env);

/*
Parsing
*/

int		ft_remplire_listes(char *s, t_temp **lst_t, t_env **lst_e);
int		ft_check_quotes(char *str);
void	ft_exit(void);
t_env	*before_while(int ac, char **av, char **env);
void	ft_free(t_temp *lst_temp, t_list *lst);
/*
Signals
*/

void	handler_sig_herdoc(int sig);
void	handler_sig(int sig);
void	handler_sig_(void);
void	ctl_quit(int sig);

/*
free
*/

void	free_lst_temp(t_temp *head_temp);
void	free_lst(t_list *lst);
void	free_lst_env(t_env *head_env);

/*
exec
*/

//....................../redirections/..................
int		ft_out(t_red *red);
int		ft_in(t_red	*red);
int		ft_appand(t_red	*red);
int		ft_execred(t_list *lst);
//....................../execution/.....................
char	*get_path(t_env *data);
char	*path(t_env *data, char *lst);
t_env	*init_env(char **env);
int		ft_exec(t_list *lst, t_env **env);
char	**get_arg(t_env *env);
t_env	*empty_env(t_env *lnv, t_env *new);
//./execution/built-ins/cd-env-pwd-echo
int		ft_run(t_list *lst, t_env **env);
void	f_exit(t_list *cmd);
void	ft_cd(t_env *env, t_list *lst);
char	*get_oldp(t_env *env);
void	ft_echo(char **content);
void	ft_pwd(t_list *lst);
char	*ft_change_pwd(char *str, char *pwd, t_env *env);
void	ftenv(t_env *env);
char	*ft_getpwd(t_env *env);
int		is_builtins(t_list *lst);
void	ft_free_env(t_env *env);
int		ft_env_cmd(t_env *env, char **content);
void	print_env(t_env *env);
t_env	*ft_env(char **nv);
//builtins export
void	ft_exp(t_env *env);
int		ft_addnode(t_env *env, char *cnt);
void	ft_printexport(t_env *env);
int		check_name(t_env *env, char *name);
int		env_len(t_env *env);
int		check_char(char *content, char c);
void	reset_pos(t_env *env);
char	*free_and(char *ptr);
char	*dup_name(char *src);
char	*check_plus(char *content);
t_env	*return_node(t_env *env, char *name);
int		is_valid(char *name, char *content);
void	ft_update(t_env *tmp, char *content, char *name);
//builtins unset
void	ft_envdelone(t_env *env, void (*del)(void*));
t_env	*ft_envnew(char *content, char *name);
void	ft_unset(t_env **env, char *content);
//./execution/check_redirections.c
int		check_redirections(t_red *red);
int		create_file(t_red *red, int fd);
//./execution/pipes
void	ft_pipe(int *fd, t_list *lst, t_env **head_env);
void	ft_dup(int *fd, int c, int p);
int		ft_fork(t_pip p, t_env *env, t_list *lst, int *fd);

#endif