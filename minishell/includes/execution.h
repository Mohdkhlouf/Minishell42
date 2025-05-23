/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:25:29 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 14:18:41 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_data			t_data;
typedef struct s_parsed_data	t_parsed_data;
typedef struct s_cmds			t_cmds;

bool							execution(t_data *data, t_parsed_data *cmds_d);
bool							is_empty_cmd(t_cmds *cmd);
bool							builtin_cmd(t_cmds *cmd, t_data *data,
									int *exit_code);
void							external_cmd(t_cmds *cmd, t_data *data,
									int *exit_code, pid_t *pid);

void							exec_cmd(t_cmds *cmd, t_data *data);
char							*find_path(t_data *data, char *cmd);
char							*join_cmd_with_slash(char *cmd);
bool							handle_pipes(t_data *data,
									t_parsed_data *cmds_d, int *exit_code);
bool							execute_pipes(t_data *data, int i,
									int *prev_cmd, int *exit_code);

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

bool							exec_heredoc(t_data *data,
									t_parsed_data *cmds_d);
int								handle_heredoc(char *input_delimiter,
									t_data *data, int expand);
void							write_free_heredoc(int fd, char *to_write,
									char *line);
void							set_g_signal(int value);
void							reset_signals_to_prompt(void);
void							handle_heredoc_signals(int sig);
int								heredoc_event_hook(void);

char							*strip_quotes(char *delim);
int								is_quoted_delimiter(char *delim);
void							heredoc_signal_rest(t_data *data);

/* extras */
void							hanlde_fd(int old, int fd);
void							not_execute_builtin(t_data *data);
void							execute_child(t_data *data, int i,
									int *prev_cmd, int *exit_code);
void							not_execve_handler(t_data *data, char *path);
void							not_access_handler(t_cmds *cmd, t_data *data,
									char *path);
void							not_path_handler(t_cmds *cmd, t_data *data);
bool							allocate_pid(t_data *data,
									t_parsed_data *cmds_d);
void							closing_heredoc(int fd);

#endif