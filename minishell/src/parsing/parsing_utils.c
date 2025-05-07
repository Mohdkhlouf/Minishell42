
#include "../includes/parsing.h"

void	init_cmd(t_cmds *cmd)
{
	cmd->red_in_fd = -1;
	cmd->red_out_fd = -1;
}

void	create_cmds_arr(t_data *data, t_parsed_data *cmds_d)
{
	int	i;

	i = 0;
	cmds_d->cmds = ft_calloc(cmds_d->cmds_counter, sizeof(t_cmds));
	if (!cmds_d->cmds)
		exit(EXIT_FAILURE);
	while (i < cmds_d->cmds_counter)
	{
		cmds_d->cmds[i].cmd = ft_calloc(data->tokens_conter + 1,
				sizeof(char *));
		if (!cmds_d->cmds[i].cmd)
			exit(EXIT_FAILURE);
		cmds_d->cmds[i].reds = ft_calloc(data->tokens_conter + 1,
				sizeof(char *));
		if (!cmds_d->cmds[i].reds)
			exit(EXIT_FAILURE);
		init_cmd(&cmds_d->cmds[i]);
		i++;
	}
}
/* when pipe found make new commands and start filling the new one*/
void	pipe_found(t_parsed_data *cmds_d)
{
	cmds_d->cmds[cmds_d->cmds_ctr].cmd[cmds_d->token_ctr] = NULL;
	cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->red_ctr] = NULL;
	/* here is a problem*/
	cmds_d->cmds_ctr++;
	cmds_d->red_ctr = 0;
	cmds_d->token_ctr = 0;
}
/* add new redirecttion from tokens to the final struct for execution*/
void	cmd_appened(t_parsed_data *cmds_d, t_data *data, int *i)
{
	if (data->tokens[*i].data[0] != '\0')
	{
		cmds_d->cmds[cmds_d->cmds_ctr].cmd[cmds_d->token_ctr] = ft_strdup(data->tokens[*i].data);
		cmds_d->token_ctr++;
	}
}
/* add new commands from tokens to the final struct for execution*/
void	redirection_appened(t_parsed_data *cmds_d, t_data *data, int *i)
{
	if (data->tokens[*i].data[0] != '\0')
	{
		cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->red_ctr] = ft_strdup(data->tokens[*i].data);
		cmds_d->red_ctr++;
	}
}