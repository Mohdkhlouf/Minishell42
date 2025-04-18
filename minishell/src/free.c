#include "../includes/minishell.h"

void	free_cmds_d(t_parsed_data *cmds_d)
{
	int	i;

	i = 0;
	if (!cmds_d || !cmds_d->cmds)
		return ;
	while (i < cmds_d->cmds_counter)
	{
		if (cmds_d->cmds[i].cmd)
			free_matrix(cmds_d->cmds[i].cmd);
		if (cmds_d->cmds[i].reds)
			free_matrix(cmds_d->cmds[i].reds);
		i++;
	}
	if (cmds_d->cmds)
	{
		free(cmds_d->cmds);
		cmds_d->cmds = NULL;
	}
}

void	free_data(t_data *data)
{
	int	i;

	/* ithingk i free some of these tokens that are moved to new pointer in the
	cmds_data so i have to check or maybe fr double free for the thinfs copied there*/
	i = 0;
	while (data->tokens && i < data->tokens_conter)
	{
		if (data->tokens[i].data)
		{
			free(data->tokens[i].data);
			data->tokens[i].data = NULL;
		}
		i++;
	}
	free(data->tokens);
	data->tokens = NULL;
}

void	free_env_list(t_var *env)
{
	t_var	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

int	free_matrix(char **env)
{
	int	i;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
	return (0);
}
