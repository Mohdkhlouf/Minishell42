#include "../includes/minishell.h"

void	command_cleanup(t_data *data, t_parsed_data *cmds_d)
{
	if (access("HEREDOC_TEMP.txt", F_OK) == 0)
	{
		if (!unlink("HEREDOC_TEMP.txt") == 0)
			perror("unlink failed");
	}
	data->pid = NULL;
	free_matrix(data->envp);
	free_cmds_d(cmds_d);
	free_data(data);
}

void	free_readingloop(t_data *data, t_parsed_data *cmds_d)
{
	free_matrix(data->parsed_path);
	free_env_list(data->env_lst);
	ft_free(data->input_line);
	free(data->tokens);
	free(data);
	free(cmds_d);
}

void	free_cmds_d(t_parsed_data *cmds_d)
{
	int	i;

	i = 0;
	if (!cmds_d || !cmds_d->cmds)
		return ;
	while (i < cmds_d->cmds_counter)
	{
		if (cmds_d->cmds[i].cmd)
			free_2arr_general(cmds_d->cmds[i].cmd);
		if (cmds_d->cmds[i].reds)
			free_2arr_general(cmds_d->cmds[i].reds);
		if (cmds_d->cmds[i].red_in_fd != -1)
			close(cmds_d->cmds[i].red_in_fd);
		if (cmds_d->cmds[i].red_out_fd != -1)
			close(cmds_d->cmds[i].red_out_fd);
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

	i = 0;
	while (data->tokens && data->tokens[i].data && i < data->tokens_conter)
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
	free(data->pid);
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
}
