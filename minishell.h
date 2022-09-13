/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:23:59 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/10 18:41:18 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char	*cmd_path;
	char	**arg;
	char	**red;
	int		*type;
	char	**limiter;
	int		in;
	int		out;
}				t_cmd;

typedef struct exec
{
	char	**envp;
	char	*cmd;
	char	**hold;
	char	*check;
	int		i;
	int		index;
}	t_exec;

typedef struct s_g_var
{
	char					**envp;
	int						save0;
	int						save1;
	unsigned long long		exit_code;
	int						n_node;
	int						dup_0;
	int						dup_1;
	char					*path;
	char					*hold;				
	pid_t					pid;
	int						check;
	int						cmp_exit;
	int						f_f;
	int						ret;
	int						sig;
	int						check_her;
	int						perm;
	int						flag;
}	t_g_var;

t_g_var	g_v;
/********************PARCING_PART__1********************/
void	parcing_function(void);
t_list	*error_handling(char *line, char **env);
void	pipeline_loop(t_list *pipeline, int *fd, t_list *head);
void	handel_echo(char *line, char **env);
void	*after_split(char *s_line);
int		ft_count(char *token);
char	*handel_many_red(char *token);
void	*check_tokens(char *token, char *value);
void	free_struct(t_list *pipiline);
char	*fill_help(char *line, int *index, int *row);

char	*expand_dollar(char *line);
char	*expand_herdoc(char *line);
char	*expand_exit_value(char *value, int *index);
char	*join_value(char *value, char c, int *index);
char	*get_value(char *value, char *buff);
char	*join_line(char *value, char *line, int *index, int *flag);
char	*expand(char *value, char *line, int *index, int *flag);
char	*get_s_quote(char *value, char *line, int *index);
char	*skip_herdoc_sign(char *value, int *index);
char	*expand_d_quote(char *value, char *line, int *index);
char	*get_buff(char *line, int *index);

int		ft_isspace(char c);
void	free_struct(t_list *pipiline);
char	**replace_pipe(char **s_line);
int		skip_herdoc(char *line, int index);
void	*ft_cpy(char *dest, char *src, int len);
char	*skip_space(char *s);
int		check_red_type(char *line, int index);
int		skip_double_quote(char *line, int index, int *count);
int		skip_single_quote(char *line, int index, int *count);
void	*ft_cpy(char *dest, char *src, int len);
void	raise_err(char err);
int		search_for_char(char *env);
int		check_condition(char c);

/*********************UTILS****************************/
void	error_msg(char *s);
void	display_msg(char *str);
int		is_quote(char c);
int		count_d_pointer(char **ptr);
int		trow_err(int d_quote, int s_quote);
int		ignore_space(char *line, int i);
char	*skip_space(char *s);
char	*add_space(char *s);
int		skip_char_inside_quote(char *line, int i, int flag);
char	*fo_strjoin(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
void	d_free(char **str);
int		ft_count_word(char *line, int index);
void	ft_putstr(char *s);
void	ft_putendl(char *s);
int		skip_word(char *line, int index, int flag);
int		skip_redirecition(char *line, int index);
char	*find_line(char **env, char *key);
void	open_herdoc(t_list *pipeline);
char	find_type_of_red(char *line);
void	allocate_fill_her(char *line, t_cmd *data, int count_her);
void	allocate_fill_arg(char *line, t_cmd *data, int count_arg);
void	allocate_fill_red(char *line, t_cmd *data, int count_red);
char	*fill_d_struct(char *line, int *index, char *str, int *row);
char	*fill_struct(char *line, int *index, char *str, int *row);

/********************CHECK_TOKENS***********************/
int		check_pipe_error(char *line);
int		redirection_error(char **s_line);
int		ft_isspace(char c);
int		is_metachar(char c);

/*******************REDIRECTION*******************/
int		count_redirection(char *line);
int		count_herdoc(char *line);
int		check_cmd(char *line, int flag);
int		count_args(char *line);
t_list	*get_full_cmd(char **s_line, char **env);
char	*find_path(char *cmd, char **envp);

/*********************BUILTINS****************************/
void	builtins(t_list *pipeline);
int		c_builtins(char *cmd);
void	ft_cd(t_list *pipeline);
void	ft_echo(t_list *pipeline);
void	ft_env(t_list *pipeline);
void	ft_exit(t_list *pipeline);
void	ft_export(t_list *pipeline, t_exec *exec);
int		ft_check_export(char *name);
void	ft_valid_export(t_list *pipeline, t_exec *exec, char *arg);
void	ft_pwd(void);
void	ft_unset(t_list *pipeline);
void	init_data(t_exec *exec);
char	*get_key(char *s);
void	free_old_env(char **env);
int		check_dup_key(char *key);
void	change_env(char *new, char *key);
void	write_expo(char **sor_exp, char **value_h);
void	write_expo_2(int i, char **sor_exp, char **value_h);
void	for_unset(t_list *pipeline, int k);
int		get_eq_s(char *str);
void	add_export(char **arg, t_list *pipeline, t_exec *exec);
void	ft_unset_tool(t_list *pipeline, char **tmp, int k);
int		check_var(char *av);

/*********************EXECUTION****************************/
int		other_cmd(t_list *pipeline, int *fd);
int		append_hand(t_list *pipeline, int i);
int		outfile_procces(t_list *pipeline, int i);
int		infile_procces(t_list *pipeline, int i);
int		open_files(t_list *pipeline, int *fd);
pid_t	ft_fork(void);
int		other_cmd_help(t_list *pipeline, int *fd);
int		other_cmd_help2(t_list *pipeline, int *fd);
void	exec_child(int *fd, t_list *pipeline);
void	help_no_type(t_list *pipeline);
int		check_unset(char *arg);
void	ft_print_error(t_list *pipeline);
int		other_cmd_tool(t_list *pipeline, int *fd);

/*********************SIGNALS****************************/
void	signals(void);
void	handel_signal(int sig);
void	rl_replace_line(const char *text, int clear_undo);

#endif