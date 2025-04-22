#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "execution.h"
# include "lexing.h"
# include "parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sched.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 1
# define FAILIURE 0

typedef struct s_parsed_data	t_parsed_data;
extern volatile sig_atomic_t		g_exit_status;

typedef enum e_token_type
{
	TOK_UNKNOWN,          // Unknown token
	TOK_COMMAND,          // Command (e.g., "ls")
	TOK_ARGUMENT,         // Argument (e.g., "file.txt")
	TOK_PIPE,             // Pipe "|" operator
	TOK_REDIRECT_IN,      // Redirect "<" operator
	TOK_REDIRECT_OUT,     // Redirect ">" operator
	TOK_APPEND,           // Append ">>" operator
	TOK_REDIRECT_HEREDOC, // Here Document "<<" operator
	TOK_SINGLE_QUOTE,     // Single quote "'" character
	TOK_DOUBLE_QUOTE,     // Double quote "\"" character
	TOK_ENV_VAR,          // Environment variable (e.g., $HOME)
	TOK_EOF,              // End of file or input termination
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
	char						*input_line;
	int							cline_parts;
	t_token						*tokens;
	size_t						end;
	size_t						start;
	bool						in_token;
	int							tokens_conter;
	bool						quote_found;
	bool						double_quote_found;
	char						quote_type;
	bool						file_seperator_found;
	bool 						variable_sign_found;
	char						*path;
	char						**parsed_path;
	char						*pwd;
	char						**words;
	t_var						*env_lst;
	char						**envp;
	int 						pipe_fd[2];
	pid_t	pid;
}								t_data;

/*---------------Parsing------------------*/

void							free_data(t_data *data);
int								line_split(t_data *data);
int								lexing(t_data *data);
int								tokenizing(t_data *data);
void							print_error(char *msg);
void							free_cmds_d(t_parsed_data *cmds_d);
void							start_signal(void);

/*---------------free-----------------------*/
int								free_matrix(char **env);
void							free_env_list(t_var *head);

// void handle_sigint(int sig);
// void handle_sigquit(int sig);
// void	cmds_process_loop(t_data *data, t_parsed_data *cmds_data);

/*---------------Built-ins--------------------*/
int								execute_builtin(t_data *data, t_cmds *cmds);
int								is_builtin(char *cmd);
/*-----------------echo----------------------*/
int								ft_echo(t_cmds *cmd, t_data *data);
int								check_nl(char *new_line);
/*------------------pwd---------------------*/
int								ft_pwd(t_cmds *cmd, t_data *data);
/*------------------env---------------------*/
int								ft_env(t_cmds *cmd, t_data *data);
void							init_env(char **envp, t_data *data);
t_var							*init_envp_node(char *env);
void							env_addtolist(t_var **lst, t_var *node);
/*-------------------cd---------------------*/
int								ft_cd(t_cmds *cmd, t_data *data);
int								cd_with_no_param(t_data *data);
int								cd_with_dash_param(t_data *data);
int								cd_with_param(t_data *data, char *path_value);
void							update_env_list(char *key, char *value,
									t_data *data);
char							*get_env_value(char *key, t_data *data);
/*------------------export-------------------*/
int								ft_export(t_cmds *cmd, t_data *data);
int								get_env_len(t_var *env);
char							**list_to_arr(int size, t_var *env);
char							**sort_arr_list(char **arr, int size);
void							export_with_param(t_cmds *cmd, t_data *data);
void							add_new_env_variable(char *key, char *value,
									t_data *data);
void							get_export(char **sorted_arr, t_data *data);
char							*get_env_key(char *key, t_data *data);
int								ft_exit(t_cmds *cmd, t_data *data);
/*--------------------unset-------------------*/
int								ft_unset(t_cmds *cmd, t_data *data);
void							update_new_env(t_data *data);
int								ft_strcmp(const char *s1, const char *s2);
#endif
// void add_export_to_list(char **arr_list, t_data *data);
// void print_export(t_data *data);
// void check_echo_$(t_data *data);
// int check$(char *sign);
// void print_env_to_envp(t_data *data);
// t_var *env_content(char *key, char *value);
// t_var *lst_new_elem(char *name, char *value);
// void lst_add_back(t_var **lst, t_var *new_node);
// t_var *lst_last(t_var *lst);
// void init_env(char **envp, t_data *data);
// void set_shlvl(t_data *data, char **envp, int i);

//
