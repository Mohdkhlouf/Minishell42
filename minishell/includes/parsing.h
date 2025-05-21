/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:26:01 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 12:26:04 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

typedef struct s_data	t_data;

typedef struct s_cmds
{
	char				**cmd;
	char				**reds;
	int					red_in_fd;
	int					red_out_fd;
	int					saved_stdout;
	int					saved_stdin;
}						t_cmds;

typedef struct s_parsed_data
{
	t_cmds				*cmds;
	int					cmds_counter;
	int					pipes_counter;
	int					cmds_ctr;
	int					red_ctr;
	int					token_ctr;
}						t_parsed_data;

bool					parsing(t_data *data, t_parsed_data *cmds_d);
void					create_cmds_arr(t_data *data, t_parsed_data *cmds_d);
void					pipe_found(t_parsed_data *cmds_d);
void					redirection_appened(t_parsed_data *cmds_d, t_data *data,
							int *i);
void					cmd_appened(t_parsed_data *cmds_d, t_data *data,
							int *i);
bool					validation(t_data *data);
void					init_cmd(t_cmds *cmd);

#endif
