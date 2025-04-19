
#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <stdbool.h>
typedef struct s_data			t_data;
typedef struct s_parsed_data	t_parsed_data;
typedef struct s_cmds			t_cmds;

void							execution(t_data *data, t_parsed_data *cmds_d);
bool							is_empty_cmd(t_cmds *cmd);
void							handle_command(t_cmds *cmd, t_data *data);
void							parse_path(t_data *data);
void							handle_empty_cmd(t_cmds *cmd, t_data *data);
int								execute_cmd(t_cmds *cmd, t_data *data);
void							exec_cmd(t_cmds *cmd, t_data *data);
char							*find_path(t_data *data, char *cmd);
char							*join_cmd_with_slash(char *cmd);
void							handle_pipes(t_data *data,
									t_parsed_data *cmds_d);
void							execute_pipes(t_data *data,
									t_parsed_data *cmds_d, int i,
									int *prev_cmd);
void							set_default_signal_handlers(void);
/*---------------redirectins------------------*/
void							execute_redirections(t_data *data,
									t_cmds *cmds_d);
void							heredoc_handller(int *i, char *delimiter);
bool							open_output_file(char *outfile, int mode);
bool							open_input_file(char *infile);
void							hanlde_fd(int old, int fd);
void	handle_single_command(t_cmds *cmd, t_data *data);

#endif