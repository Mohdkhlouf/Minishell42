/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:02:18 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/03/28 11:49:41 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexing.h"

void	normal_function(t_data *data)
{
	data->in_token = true;
	if (data->input_line[data->end] == '\''
		|| data->input_line[data->end] == '\"')
	{
		if (data->quote_found == true)
			data->quote_found = false;
		else if (data->quote_found == false)
			data->quote_found = true;
	}
}

void	env_variable_function(t_data *data)
{
	if (data->in_token)
	{
		append_token(data, TOK_ENV_VAR);
		data->in_token = false;
	}
	data->start = data->end;
}

void	eof_function(t_data *data)
{
	if (data->double_quote_found || data->quote_found)
	{
		printf("quotes are not closed");
		exit(FAILIURE);
	}
	if (data->in_token)
	{
		append_token(data, TOK_UNKNOWN);
		data->in_token = false;
	}
	data->start = data->end;
	append_token(data, TOK_EOF);
	data->start = data->end + 1;
}
