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

void	free_env_list(t_var *env)
{
	t_var	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
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
	if (env)
		free(env);
	env = NULL;
	return (0);
}

int	free_2arr_general(char **arr)
{
	int	i;

	if (!arr)
		return (1);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (0);
}

void	cleanup_minishell(t_data *data)
{
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	free_matrix(data->envp);
	free_2arr_general(data->parsed_path);
	free_2arr_general(data->words);
	ft_free(data->pwd);
	ft_free(data->input_line);
	free_env_list(data->env_lst);
	free_cmds_d(data->cmds_d);
	free_data(data);
	free(data->cmds_d);
	// free(data);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
// void free_env_list(t_var *env)
// {
// 	while (env)
// 	{
// 		if (env->key)
// 		{
// 			free(env->key);
// 			env->key = NULL;
// 		}
// 		if (env->value)
// 		{
// 			free(env->value);
// 			env->value = NULL;
// 		}
// 		if (env)
// 			free(env);
// 		env = env->next;
// 	}
// }

// void free_env_list(t_var *env)
// {
// 	t_var *tmp;

// 	while (env)
// 	{
// 		tmp = env->next;
// 		if (env->key)
// 			free(env->key);
// 		if (env->value)
// 			free(env->value);
// 		free(env); // <- FREE THE NODE
// 		env = tmp;
// 	}
// }