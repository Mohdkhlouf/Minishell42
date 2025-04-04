/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:17:36 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/04 15:55:33 by mkhlouf          ###   ########.fr       */
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
}						t_cmds;

typedef struct s_parsed_data
{
	t_cmds				*cmds;
	int 				cmds_counter;
	int 				pipes_counter;
	int	cmds_ctr;
	int	redirect_counter;
	int	token_counter;
}						t_parsed_data;


void					parsing(t_data *data, t_parsed_data *cmds_data);

#endif