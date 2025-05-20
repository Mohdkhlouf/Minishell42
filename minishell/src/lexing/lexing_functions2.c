/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:59:32 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/20 13:59:33 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexing.h"

void	malloc_fail(t_vars_data *var, t_data *data)
{
	ft_free(var->temp);
	free_var(var);
	command_cleanup(data, data->cmds_d);
	exit(1);
}

bool	process_add(t_vars_data *var, char *temp)
{
	var->vars_arr[var->parts_count] = ft_strdup(temp);
	if (!var->vars_arr[var->parts_count])
	{
		ft_free(temp);
		var->var_malloc_flag = true;
		return (false);
	}
	ft_free(temp);
	var->parts_count++;
	return (true);
}

/* this function to continue when the input is nprmal not from the needed
charaters*/
void	normal_function(t_data *data)
{
	data->in_token = true;
	if (data->input_line[data->end] == '\'')
	{
		if (data->quote_found == true)
			data->quote_found = false;
		else if (data->quote_found == false)
			data->quote_found = true;
		if (data->first_quote_type == 0)
			data->first_quote_type = 1;
	}
	if (data->input_line[data->end] == '\"')
	{
		if (data->double_quote_found == true)
			data->double_quote_found = false;
		else if (data->double_quote_found == false)
			data->double_quote_found = true;
		if (data->first_quote_type == 0)
			data->first_quote_type = 2;
	}
	if (data->variable_sign_found)
		data->variable_sign_found = false;
}

/* this funcction to add variable tokens like $HOME*/
void	env_variable_function(t_data *data)
{
	if (data->in_token)
	{
		append_token(data, TOK_ENV_VAR);
		data->in_token = false;
	}
	data->start = data->end;
}

/* this funcction to add the end of line null terminator as a seperate token*/
void	eof_function(t_data *data)
{
	if (data->in_token)
	{
		append_token(data, TOK_UNKNOWN);
		data->in_token = false;
	}
	if (data->variable_sign_found)
		data->variable_sign_found = false;
	data->start = data->end;
	data->start = data->end + 1;
}
