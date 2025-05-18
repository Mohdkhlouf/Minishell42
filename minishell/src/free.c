#include "../includes/minishell.h"

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
