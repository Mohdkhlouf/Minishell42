/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:20:09 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/02 15:17:36 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void data_init(t_data *data)
{
	data->cline_parts = 0;
	data->input_line = NULL;
	data->tokens = NULL;
	data->end = 0;
	data->start = 0;
	data->in_token = false;
	data->tokens_conter = 0;
	data->quote_found = false;
	data->double_quote_found = false;
	data->quote_type = 0;
	data->file_seperator_found = false;
}

void reading_loop(t_data *data)
{
	while (true)
	{
		data_init(data);
		data->input_line = readline("Prompt> ");
		if (!data->input_line)
		{
			printf("Exit");
			free(data->input_line);
			return;
		}
		add_history(data->input_line);
		lexing(data);
		tokenizing(data);
		parsing(data);
		free_data(data);
	}
}


int	main(void)
{
	t_data *data;
	
	data = malloc(sizeof (t_data));
	if(!data)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	data_init(data);
	reading_loop(data);
	free(data);
	return (EXIT_SUCCESS);
}
