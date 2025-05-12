
#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <stdbool.h>

// static int						g_heredoc_interrupted = 0;

typedef struct s_data			t_data;
typedef struct s_parsed_data	t_parsed_data;
typedef struct s_cmds			t_cmds;

bool							execution(t_data *data, t_parsed_data *cmds_d);
bool							is_empty_cmd(t_cmds *cmd);
bool								builtin_cmd(t_cmds *cmd, t_data *data,
									int *exit_code);
void							parse_path(t_data *data);
void							handle_empty_cmd(t_cmds *cmd, t_data *data);
void	external_cmd(t_cmds *cmd, t_data *data, int *exit_code, pid_t *pid);

void							exec_cmd(t_cmds *cmd, t_data *data);
char							*find_path(t_data *data, char *cmd);
char							*join_cmd_with_slash(char *cmd);
bool							handle_pipes(t_data *data,
									t_parsed_data *cmds_d, int *exit_code);
bool							execute_pipes(t_data *data,
									t_parsed_data *cmds_d, int i, int *prev_cmd,
									int *exit_code);
void							set_default_signal_handlers(void);

/*---------------redirectins------------------*/
bool							execute_redirections(t_data *data,
									t_cmds *cmds_d, int *exit_code);
bool							open_output_file(t_cmds *cmd, char *outfile,
									int mode);
bool							open_input_file(t_cmds *cmd, char *infile);
void							hanlde_fd(int old, int fd);
void							handle_single_command(t_cmds *cmd, t_data *data,
									int *exit_code);
void							set_prompt_signals(void);
void							set_child_signals(void);

/*------------------heredoc------------------*/

bool exec_heredoc(t_data *data, t_parsed_data *cmds_d);
int								handle_heredoc(char *input_delimiter, t_data *data, int expand);
char 							*strip_quotes(char *delim);
int 							is_quoted_delimiter(char *delim);
// int								get_heredoc_fd(void);
// void							heredoc_handller(int *i, char *delimiter);
void heredoc_signal_rest(t_data *data);

#endif