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
/*to create new array for commands and arguments */
/*to create new array for redirections*/

/*to fill in data from tokens struct to the commands struct*/
void	fill_in_arr(t_parsed_data *cmds_d, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tokens_conter)
	{
		if ((data->tokens_conter > 1) && (data->tokens[0].type == TOK_ENV_VAR) && (data->tokens[0].data[0] == 0) && (i == 0))
		{
			i++;
			continue;
		}
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

/*testing function to print commands and redirections*/
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
		if (cmds_d->cmds[i].reds[j] && cmds_d->cmds[i].reds)
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

bool	parsing(t_data *data, t_parsed_data *cmds_d)
{
	find_cmds_counter(data, cmds_d);
	create_cmds_arr(data, cmds_d);
	fill_in_arr(cmds_d, data);
	// printing_cmds_reds(cmds_d);
	return (true);
}
