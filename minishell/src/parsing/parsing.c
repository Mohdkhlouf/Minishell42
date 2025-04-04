/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:56:54 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/04 16:07:17 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	cmds_init(t_parsed_data *cmds_data)
{
	cmds_data->cmds_counter = 0;
	cmds_data->pipes_counter = 0;
	cmds_data->cmds_ctr = 0;
	cmds_data->red_ctr = 0;
	cmds_data->token_ctr = 0;
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
		// Allocate memory for reds (assuming a max of 5 reds per command)
		cmds_data->cmds[i].reds = malloc(sizeof(char *) * 20);
		if (!cmds_data->cmds[i].reds)
			exit(EXIT_FAILURE);
	}
}

void	pipe_found(t_parsed_data *cmds_data)
{
	cmds_data->cmds[cmds_data->cmds_ctr].cmd[cmds_data->token_ctr] = NULL;
	cmds_data->cmds[cmds_data->cmds_ctr].reds[cmds_data->token_ctr] = NULL;
	cmds_data->cmds_ctr++;
	cmds_data->red_ctr = 0;
	cmds_data->token_ctr = 0;
}

void	redirection_appened(t_parsed_data *cmds_data, t_data *data, int *i)
{
	cmds_data->cmds[cmds_data->cmds_ctr].cmd[cmds_data->token_ctr] = data->tokens[*i].data;
	cmds_data->token_ctr++;
}

void	cmd_appened(t_parsed_data *cmds_data, t_data *data, int *i)
{
	cmds_data->cmds[cmds_data->cmds_ctr].reds[cmds_data->red_ctr] = data->tokens[*i].data;
	cmds_data->red_ctr++;
}

void	fill_in_arr(t_parsed_data *cmds_data, t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i].type != TOK_EOF)
	{
		if (data->tokens[i].type == TOK_PIPE)
			pipe_found(cmds_data);
		else
		{
			if (data->tokens[i].type == TOK_REDIRECT_HEREDOC
				|| data->tokens[i].type == TOK_REDIRECT_IN
				|| data->tokens[i].type == TOK_REDIRECT_OUT
				|| data->tokens[i].type == TOK_APPEND)
			{
				cmd_appened(cmds_data, data, &i);
			}
			else
				redirection_appened(cmds_data, data, &i);
		}
		i++;
	}
	cmds_data->cmds[cmds_data->cmds_ctr].cmd[cmds_data->token_ctr] = NULL;
	cmds_data->cmds[cmds_data->cmds_ctr].reds[cmds_data->red_ctr] = NULL;
}

void	printing_cmds_reds(t_parsed_data *cmds_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("i have %d commands\n", cmds_data->cmds_counter);
	while (i < cmds_data->cmds_counter)
	{
		j = 0;
		printf("Final Command %d: ", i);
		while (cmds_data->cmds[i].cmd[j])
		{
			printf("%s ", cmds_data->cmds[i].cmd[j]);
			j++;
		}
		printf("#\n");
		printf("Final reds %d: ", i);
		j = 0;
		if (cmds_data->cmds[i].reds[j])
		{
			while (cmds_data->cmds[i].reds[j])
			{
				printf("%s ", cmds_data->cmds[i].reds[j]);
				j++;
			}
		}
		else
		{
			printf("No reds");
		}
		printf("#\n");
		i++;
	}
}
void	parsing(t_data *data, t_parsed_data *cmds_data)
{
	find_cmds_counter(data, cmds_data);
	create_cmds_arr(cmds_data);
	fill_in_arr(cmds_data, data);
	printing_cmds_reds(cmds_data);
}
