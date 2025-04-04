/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:56:54 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/04 15:26:55 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	cmds_init(t_parsed_data *cmds_data)
{
	cmds_data->cmds_counter = 0;
	cmds_data->pipes_counter = 0;
}

void	find_cmds_counter(t_data *data, t_parsed_data *cmds_data)
{
	int	i;

	i = 0;
	cmds_init(cmds_data);
	while (data->input_line[i])
	{
		if (data->input_line[i] == '|')
			cmds_data->pipes_counter++;
		i++;
	}
	cmds_data->cmds_counter = cmds_data->pipes_counter + 1;
}

void	create_cmds_arr(t_parsed_data *cmds_data)
{
	cmds_data->cmds = malloc(sizeof(t_cmds) * cmds_data->cmds_counter);
	if (!cmds_data->cmds)
		exit(EXIT_FAILURE);
	for (int i = 0; i < cmds_data->cmds_counter; i++)
	{
		cmds_data->cmds[i].cmd = malloc(sizeof(char *) * 20);
		if (!cmds_data->cmds[i].cmd)
			exit(EXIT_FAILURE);
		// Allocate memory for redirections (assuming a max of 5 redirections per command)
		cmds_data->cmds[i].redirections = malloc(sizeof(char *) * 20);
		if (!cmds_data->cmds[i].redirections)
			exit(EXIT_FAILURE);
	}
}

void	fill_in_arr(t_parsed_data *cmds_data, t_data *data)
{
	int	i;
	int	cmds_ctr;
	int	redirect_counter;
	int	token_counter;

	i = 0;
	cmds_ctr = 0;
	redirect_counter = 0;
	token_counter = 0;
	while (data->tokens[i].type != TOK_EOF)
	{
		if (data->tokens[i].type == TOK_PIPE)
		{
			cmds_data->cmds[cmds_ctr].cmd[token_counter] = NULL;
			cmds_data->cmds[cmds_ctr].redirections[token_counter] = NULL;
			cmds_ctr++;
			redirect_counter = 0;
			token_counter = 0;
		}
		else
		{
			if (data->tokens[i].type == TOK_REDIRECT_HEREDOC
				|| data->tokens[i].type == TOK_REDIRECT_IN
				|| data->tokens[i].type == TOK_REDIRECT_OUT
				|| data->tokens[i].type == TOK_APPEND)
			{
				cmds_data->cmds[cmds_ctr].redirections[redirect_counter] = data->tokens[i].data;
				redirect_counter++;
			}
			else
			{
				cmds_data->cmds[cmds_ctr].cmd[token_counter] = data->tokens[i].data;
				token_counter++;
			}
		}
		i++;
	}
	cmds_data->cmds[cmds_ctr].cmd[token_counter] = NULL;
	cmds_data->cmds[cmds_ctr].redirections[redirect_counter] = NULL;
}

void	parsing(t_data *data)
{
	int				i;
	int				j;
	t_parsed_data	*cmds_data;

	i = 0;
	j = 0;
	cmds_data = malloc(sizeof(t_parsed_data));
	if (!cmds_data)
		exit(EXIT_FAILURE);
	find_cmds_counter(data, cmds_data);
	create_cmds_arr(cmds_data);
	fill_in_arr(cmds_data, data);
	printf("i have %d commands\n", cmds_data->cmds_counter);
	while (i < cmds_data->cmds_counter)
	{
		j = 0;
		printf("Final Command %d: ", i);
		while (cmds_data->cmds[i].cmd[j])
		{
			printf("%s\n", cmds_data->cmds[i].cmd[j]);	
			j++;
		}
		printf("#\n");

		//Akancha addition for builtins
		cmds_process_loop(data, cmds_data);
		
		printf("Final Redirections %d: ", i);
		j = 0;
		if (cmds_data->cmds[i].redirections[j])
		{
			while (cmds_data->cmds[i].redirections[j])
			{
				printf("%s ", cmds_data->cmds[i].redirections[j]);
				j++;
			}
		}
		else
		{
			printf("No redirections");
		}
		printf("#\n");
		i++;
	}
}
