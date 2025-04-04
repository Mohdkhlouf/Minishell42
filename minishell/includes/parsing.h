/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:17:36 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/04 15:26:41 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_data	t_data;

void					parsing(t_data *data);

typedef struct s_cmds
{
	char				**cmd;
	char				**redirections;
}						t_cmds;

typedef struct s_parsed_data
{
	t_cmds				*cmds;
	int					cmds_counter;
	int					pipes_counter;
}						t_parsed_data;

void	cmds_process_loop(t_data *data, t_parsed_data *cmds_data);

#endif