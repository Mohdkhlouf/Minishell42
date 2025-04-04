/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:17:36 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/04 14:52:15 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"
# include <stdbool.h>
# define DELEMETERS " \t\n\0"
# define VAR_DELEMITER "/\'\"$"

typedef struct s_data	t_data;

typedef struct s_vars_data
{
	char				**vars_arr;
	int					parts_count;
	int					vars_count;
	char				*temp;
	char				*var_var;
	int					len;
	bool				var_is_found;
}						t_vars_data;

void					space_function(t_data *data);
void					pipe_function(t_data *data);
void					redirectin_function(t_data *data);
void					redirectout_function(t_data *data);
void					append_token_double(t_data *data, int type);
void					normal_function(t_data *data);
void					append_token(t_data *data, int type);
void					env_variable_function(t_data *data);
void					eof_function(t_data *data);
void					search_for_file_seperator(t_data *data, int i, int len,
							int *j);
int						find_vars_count(t_data *data, int i);
void					path_set_and_join(t_data *data, int i, char *temp,
							char *path);
void					search_for_file_seperator(t_data *data, int i, int len,
							int *j);
void					var_init(t_vars_data *var, t_data *data, int i);
void					var_handler2(t_data *data, int i);
void					print_tokens(t_data *data);
void					free_var(t_vars_data *var);

#endif