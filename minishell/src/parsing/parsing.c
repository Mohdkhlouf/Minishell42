/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:56:54 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/04 16:10:32 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	cmds_init(t_parsed_data *cmds_d)
{
	cmds_d->cmds_counter = 0;
	cmds_d->pipes_counter = 0;
	cmds_d->cmds_ctr = 0;
	cmds_d->red_ctr = 0;
	cmds_d->token_ctr = 0;
}

void	find_cmds_counter(t_data *data, t_parsed_data *cmds_d)
{
	int	i;

	i = 0;
	cmds_init(cmds_d);
	while (data->input_line[i])
	{
		if (data->input_line[i] == '|')
			cmds_d->pipes_counter++;
		i++;
	}
	cmds_d->cmds_counter = cmds_d->pipes_counter + 1;
}

void	create_cmds_arr(t_parsed_data *cmds_d)
{
	cmds_d->cmds = malloc(sizeof(t_cmds) * cmds_d->cmds_counter);
	if (!cmds_d->cmds)
		exit(EXIT_FAILURE);
	for (int i = 0; i < cmds_d->cmds_counter; i++)
	{
		cmds_d->cmds[i].cmd = malloc(sizeof(char *) * 20);
		if (!cmds_d->cmds[i].cmd)
			exit(EXIT_FAILURE);
		// Allocate memory for reds (assuming a max of 5 reds per command)
		cmds_d->cmds[i].reds = malloc(sizeof(char *) * 20);
		if (!cmds_d->cmds[i].reds)
			exit(EXIT_FAILURE);
	}
}

void	pipe_found(t_parsed_data *cmds_d)
{
	cmds_d->cmds[cmds_d->cmds_ctr].cmd[cmds_d->token_ctr] = NULL;
	cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->token_ctr] = NULL;
	cmds_d->cmds_ctr++;
	cmds_d->red_ctr = 0;
	cmds_d->token_ctr = 0;
}

void	redirection_appened(t_parsed_data *cmds_d, t_data *data, int *i)
{
	cmds_d->cmds[cmds_d->cmds_ctr].cmd[cmds_d->token_ctr] = data->tokens[*i].data;
	cmds_d->token_ctr++;
}

void	cmd_appened(t_parsed_data *cmds_d, t_data *data, int *i)
{
	cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->red_ctr] = data->tokens[*i].data;
	cmds_d->red_ctr++;
}

void	fill_in_arr(t_parsed_data *cmds_d, t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i].type != TOK_EOF)
	{
		if (data->tokens[i].type == TOK_PIPE)
			pipe_found(cmds_d);
		else
		{
			if (data->tokens[i].type == TOK_REDIRECT_HEREDOC
				|| data->tokens[i].type == TOK_REDIRECT_IN
				|| data->tokens[i].type == TOK_REDIRECT_OUT
				|| data->tokens[i].type == TOK_APPEND)
			{
				cmd_appened(cmds_d, data, &i);
			}
			else
				redirection_appened(cmds_d, data, &i);
		}
		i++;
	}
	cmds_d->cmds[cmds_d->cmds_ctr].cmd[cmds_d->token_ctr] = NULL;
	cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->red_ctr] = NULL;
}

void	printing_cmds_reds(t_parsed_data *cmds_d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("i have %d commands\n", cmds_d->cmds_counter);
	while (i < cmds_d->cmds_counter)
	{
		j = 0;
		printf("Final Command %d: ", i);
		while (cmds_d->cmds[i].cmd[j])
		{
			printf("%s ", cmds_d->cmds[i].cmd[j]);
			j++;
		}
		printf("#\n");
		printf("Final reds %d: ", i);
		j = 0;
		if (cmds_d->cmds[i].reds[j])
		{
			while (cmds_d->cmds[i].reds[j])
			{
				printf("%s ", cmds_d->cmds[i].reds[j]);
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
void	parsing(t_data *data, t_parsed_data *cmds_d)
{
	find_cmds_counter(data, cmds_d);
	create_cmds_arr(cmds_d);
	fill_in_arr(cmds_d, data);
	printing_cmds_reds(cmds_d);
}
