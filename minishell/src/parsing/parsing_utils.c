/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:02:08 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/20 14:02:54 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	clean_exit(t_data *data, t_parsed_data *cmds_d)
{
	command_cleanup(data, cmds_d);
	exit(1);
}

void	create_cmds_arr(t_data *data, t_parsed_data *cmds_d)
{
	int	i;

	i = 0;
	cmds_d->cmds = ft_calloc(cmds_d->cmds_counter, sizeof(t_cmds));
	if (!cmds_d->cmds)
		clean_exit(data, cmds_d);
	while (i < cmds_d->cmds_counter)
	{
		cmds_d->cmds[i].cmd = ft_calloc(data->tokens_conter + 1,
				sizeof(char *));
		if (!cmds_d->cmds[i].cmd)
			clean_exit(data, cmds_d);
		cmds_d->cmds[i].reds = ft_calloc(data->tokens_conter + 1,
				sizeof(char *));
		if (!cmds_d->cmds[i].reds)
			clean_exit(data, cmds_d);
		init_cmd(&cmds_d->cmds[i]);
		i++;
	}
}

/* when pipe found make new commands and start filling the new one*/
void	pipe_found(t_parsed_data *cmds_d)
{
	cmds_d->cmds[cmds_d->cmds_ctr].cmd[cmds_d->token_ctr] = NULL;
	cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->red_ctr] = NULL;
	cmds_d->cmds_ctr++;
	cmds_d->red_ctr = 0;
	cmds_d->token_ctr = 0;
}

/* add new redirecttion from tokens to the final struct for execution*/
void	cmd_appened(t_parsed_data *cmds_d, t_data *data, int *i)
{
	char	**temp_cmd;

	temp_cmd = &cmds_d->cmds[cmds_d->cmds_ctr].cmd[cmds_d->token_ctr];
	if (data->tokens[*i].data != NULL)
	{
		free(*temp_cmd);
		*temp_cmd = ft_strdup(data->tokens[*i].data);
		if (!*temp_cmd)
			clean_exit(data, cmds_d);
		cmds_d->token_ctr++;
	}
}

/* add new commands from tokens to the final struct for execution*/
void	redirection_appened(t_parsed_data *cmds_d, t_data *data, int *i)
{
	if (data->tokens[*i].data[0] != '\0')
	{
		cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->red_ctr]
			= ft_strdup(data->tokens[*i].data);
		if (!cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->red_ctr])
			clean_exit(data, cmds_d);
		cmds_d->red_ctr++;
	}
}
