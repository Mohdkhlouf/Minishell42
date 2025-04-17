
#include "../includes/parsing.h"

void	create_cmds_arr(t_parsed_data *cmds_d)
{
	cmds_d->cmds = malloc(sizeof(t_cmds) * cmds_d->cmds_counter);
	if (!cmds_d->cmds)
		exit(EXIT_FAILURE);
	ft_memset(cmds_d->cmds, 0, sizeof(t_cmds) * cmds_d->cmds_counter);
	for (int i = 0; i < cmds_d->cmds_counter; i++)
	{
		cmds_d->cmds[i].cmd = malloc(sizeof(char *) * 100);
		if (!cmds_d->cmds[i].cmd)
			exit(EXIT_FAILURE);
		cmds_d->cmds[i].reds = malloc(sizeof(char *) * 100);
		if (!cmds_d->cmds[i].reds)
			exit(EXIT_FAILURE);
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
	cmds_d->cmds[cmds_d->cmds_ctr].cmd[cmds_d->token_ctr] = ft_strdup(data->tokens[*i].data);
	cmds_d->token_ctr++;
}
/* add new commands from tokens to the final struct for execution*/
void	redirection_appened(t_parsed_data *cmds_d, t_data *data, int *i)
{
	cmds_d->cmds[cmds_d->cmds_ctr].reds[cmds_d->red_ctr] = ft_strdup(data->tokens[*i].data);
	cmds_d->red_ctr++;
}