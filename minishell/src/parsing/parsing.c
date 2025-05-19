#include "../includes/parsing.h"

/*initialize the data for the struct*/
void	cmds_init(t_parsed_data *cmds_d)
{
	cmds_d->cmds_counter = 0;
	cmds_d->pipes_counter = 0;
	cmds_d->cmds_ctr = 0;
	cmds_d->red_ctr = 0;
	cmds_d->token_ctr = 0;
}

/*function to re read the line and count the pipes so we know how
many commands we will have*/
void	find_cmds_counter(t_data *data, t_parsed_data *cmds_d)
{
	int	i;

	i = 0;
	cmds_init(cmds_d);
	while (i < data->tokens_conter)
	{
		if (data->tokens[i].type == TOK_PIPE)
			cmds_d->pipes_counter++;
		i++;
	}
	cmds_d->cmds_counter = cmds_d->pipes_counter + 1;
}

bool	chc_no_var_cmd(t_data *data, int *i)
{
	if ((data->tokens_conter > 1) && (data->tokens[0].type == TOK_ENV_VAR)
		&& (data->tokens[0].data[0] == 0) && (*i == 0))
	{
		(*i)++;
		return (false);
	}
	return (true);
}

/*to fill in data from tokens struct to the commands struct*/
void	fill_in_arr(t_parsed_data *cmds_d, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tokens_conter)
	{
		if (!chc_no_var_cmd(data, &i))
			continue ;
		if (data->tokens[i].type == TOK_PIPE)
			pipe_found(cmds_d);
		else
		{
			if (data->tokens[i].type == TOK_REDIRECT_HEREDOC
				|| data->tokens[i].type == TOK_REDIRECT_IN
				|| data->tokens[i].type == TOK_REDIRECT_OUT
				|| data->tokens[i].type == TOK_APPEND)
			{
				redirection_appened(cmds_d, data, &i);
			}
			else
				cmd_appened(cmds_d, data, &i);
		}
		i++;
	}
	cmds_d->cmds[cmds_d->cmds_ctr].cmd[cmds_d->token_ctr] = NULL;
	cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->red_ctr] = NULL;
}

bool	parsing(t_data *data, t_parsed_data *cmds_d)
{
	find_cmds_counter(data, cmds_d);
	create_cmds_arr(data, cmds_d);
	fill_in_arr(cmds_d, data);
	return (true);
}
