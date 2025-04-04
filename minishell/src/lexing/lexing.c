/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:02:18 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/04 11:56:16 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexing.h"

int	malloc_tokens_arr(t_data *data)
{
	data->cline_parts = ft_strlen(data->input_line);
	if (data->cline_parts != 0)
	{
		data->tokens = malloc(sizeof(t_token) * data->cline_parts);
		if (!data->tokens)
		{
			print_error("Error allocating memory for tokens\n");
			free(data);
			exit(EXIT_FAILURE);
		}
		return (SUCCESS);
	}
	return (FAILIURE);
}

// this one to add the data normally
void	append_token(t_data *data, int type)
{
	if (data->end == data->start)
		data->tokens[data->tokens_conter].data = ft_substr(data->input_line,
				data->start, 1);
	else
		data->tokens[data->tokens_conter].data = ft_substr(data->input_line,
				data->start, data->end - data->start);
	data->tokens[data->tokens_conter].type = type;
	data->tokens_conter++;
}

int	line_split(t_data *data)
{
	while (true)
	{
		if (data->input_line[data->end] == '\0')
			return (eof_function(data), FAILIURE);
		if (data->quote_found && data->input_line[data->end] != '\'')
			normal_function(data);
		else if (data->double_quote_found && data->input_line[data->end] != '\"'
			&& data->input_line[data->end] != '$')
			normal_function(data);
		else if (ft_strchr(DELEMETERS, data->input_line[data->end]))
			space_function(data);
		else if (data->input_line[data->end] == '|')
			pipe_function(data);
		else if (data->input_line[data->end] == '>')
			redirectout_function(data);
		else if (data->input_line[data->end] == '<')
			redirectin_function(data);
		else if (data->input_line[data->end] == '$' && !data->quote_found)
			env_variable_function(data);
		else
			normal_function(data);
		data->end++;
	}
	return (SUCCESS);
}

int	lexing(t_data *data)
{
	// int	i;

	// i = 0;
	if (malloc_tokens_arr(data) != SUCCESS)
		return (FAILIURE);
	if (line_split(data) != SUCCESS)
		return (FAILIURE);
	return (SUCCESS);
}
