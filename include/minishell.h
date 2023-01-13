/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:32:59 by ajafy             #+#    #+#             */
/*   Updated: 2023/01/13 15:08:52 by ajafy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<fcntl.h>
# include<curses.h>
# include<stdlib.h>
# include<unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define INFILE 10
# define OUTFILE 11
# define HERDOC 12
# define APPAND 13

int	g_exit_status;

/*
	Redirections_list
*/

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
	struct s_env	*next;
}	t_env;

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
Signals
*/

void	handler_sig_herdoc(int sig);
void	handler_sig(int sig);

/*
free
*/

void	free_lst_temp(t_temp *head_temp);
void	free_lst(t_list *lst);

#endif