/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:25:54 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 13:02:33 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "execution.h"
# include "lexing.h"
# include "parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sched.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 1
# define FAILIURE 0

typedef struct s_parsed_data	t_parsed_data;
extern volatile sig_atomic_t	g_signal_status;

typedef enum e_token_type
{
	TOK_UNKNOWN,
	TOK_COMMAND,
	TOK_ARGUMENT,
	TOK_PIPE,
	TOK_REDIRECT_IN,
	TOK_REDIRECT_OUT,
	TOK_APPEND,
	TOK_REDIRECT_HEREDOC,
	TOK_SINGLE_QUOTE,
	TOK_DOUBLE_QUOTE,
	TOK_ENV_VAR,
	TOK_EOF,
	TOK_STRING,
}								t_token_type;

typedef struct s_token
{
	char						*data;
	t_token_type				type;
}								t_token;

typedef struct s_var
{
	char						*key;
	char						*value;
	char						meaning;
	struct s_var				*next;
}								t_var;

typedef struct s_data
{
	t_parsed_data				*cmds_d;
	t_token						*tokens;
	size_t						end;
	size_t						start;
	t_var						*env_lst;
	pid_t						*pid;
	bool						in_token;
	bool						quote_found;
	bool						double_quote_found;
	int							first_quote_type;
	bool						file_seperator_found;
	bool						variable_sign_found;
	char						*input_line;
	char						quote_type;
	char						*path;
	char						**parsed_path;
	char						*pwd;
	char						**words;
	char						**envp;
	int							pipe_fd[2];
	int							exit_code;
	int							cline_parts;
	int							tokens_conter;
	char						*prompt;
	bool						sigquit_flag;
	bool						sigterm_flag;
	char						*file_name;
	char						*with_slash;
	bool						malloc_fail_flag;
	char						*new_delim;
	char						*old_delim;
	char						*here_line;
	int							here_ret;
	char						*here_to_write;
}								t_data;

/*---------------Parsing------------------*/

void							free_data(t_data *data);
int								line_split(t_data *data);
bool							lexing(t_data *data);
bool							tokenizing(t_data *data);
void							print_error(char *msg);
void							minishell_error(char *context, char *message,
									char *errorfile);
void							free_cmds_d(t_parsed_data *cmds_d);
void							start_signal(void);

/*---------------free-----------------------*/
int								free_matrix(char **env);
void							free_env_list(t_var *head);

/*----------------Shlvl----------------------*/
void							shelvl(t_data *data);
void							exit_shlvl(t_data *data);

/*---------------Built-ins--------------------*/
bool							execute_builtin(t_data *data, t_cmds *cmds,
									int *exit_code);
int								is_builtin(char *cmd);
/*-----------------echo----------------------*/
bool							ft_echo(t_cmds *cmd, t_data *data,
									int *exit_code);
int								check_nl(char *new_line);
/*------------------pwd---------------------*/
bool							ft_pwd(t_cmds *cmd, t_data *data,
									int *exit_code);
/*------------------env---------------------*/
bool							ft_env(t_cmds *cmd, t_data *data,
									int *exit_code);
bool							init_env(char **envp, t_data *data);
t_var							*init_envp_node(char *env);
void							env_addtolist(t_var **lst, t_var *node);
int								get_env_len(t_var *env);
/*-------------------cd---------------------*/
bool							ft_cd(t_cmds *cmd, t_data *data,
									int *exit_code);
void							update_env_list(char *key, char *value,
									t_data *data);
char							*get_env_value(char *key, t_data *data);
void							check_on_fail_cd(int *exit_code,
									char *expanded);
char							*expand_path(t_data *data, char *path_value,
									int *exit_code);
bool							change_to_home_dir(t_data *data, char *home_dir,
									int *exit_code);
bool							update_pwd_and_oldpwd(t_data *data,
									char *expanded, char *oldpwd,
									int *exit_code);
/*------------------export-------------------*/

bool							ft_export(t_cmds *cmd, t_data *data,
									int *exit_code);
int								get_env_len(t_var *env);
void							export_with_param(t_cmds *cmd, t_data *data,
									int *exit_code);
void							add_new_env_variable(char *key, char *value,
									t_data *data);
void							get_export(char **sorted_arr, t_data *data);
char							*get_env_key(char *key, t_data *data);
void							free_split(char **str);
bool							check_valid_identifier(char *key,
									char *param_value);

/*---------------------exit-------------------*/
bool							ft_exit(t_cmds *cmd, t_data *data,
									int *exit_code);
/*--------------------unset-------------------*/
bool							ft_unset(t_cmds *cmd, t_data *data,
									int *exit_code);
bool							update_new_env(t_data *data);
int								ft_strcmp(const char *s1, const char *s2);
void							command_cleanup(t_data *data,
									t_parsed_data *cmds_d);
int								free_2arr_general(char **arr);
void							cleanup_minishell(t_data *data);
void							print_error_2msgs(char *msg1, char *msg2);
void							set_path(t_data *data);
void							free_readingloop(t_data *data,
									t_parsed_data *cmds_d);
void							command_cleanup(t_data *data,
									t_parsed_data *cmds_d);
bool							pre_validation(t_data *data);
void							signal_130(t_data *data);
void							faild_read_line(t_data *data,
									t_parsed_data *cmds_d);
void							printing_cmds_reds(t_parsed_data *cmds_d);
void							ft_close(int *fd);

#endif