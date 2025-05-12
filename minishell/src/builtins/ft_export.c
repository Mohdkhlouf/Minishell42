#include "../../includes/minishell.h"

static char	**list_to_arr(int size, t_var *env)
{
	char	**arr_str;
	int		i;

	i = 0;
	arr_str = malloc(sizeof(char *) * (size + 1));
	if (!arr_str)
		return (NULL);
	while (env)
	{
		arr_str[i] = ft_strdup(env->key);
		env = env->next;
		i++;
	}
	arr_str[i] = NULL;
	return (arr_str);
}

static int	swap_arr(char **arr, int limit)
{
	int		i;
	int		swapped;
	char	*temp;

	i = 0;
	swapped = 0;
	while (i < limit)
	{
		if (ft_strcmp(arr[i], arr[i + 1]) > 0)
		{
			temp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = temp;
			swapped = 1;
		}
		i++;
	}
	return (swapped);
}

static char	**sort_arr_list(char **arr, int size)
{
	int	j;
	int	swapped;

	j = 0;
	while (j < size - 1)
	{
		swapped = swap_arr(arr, size - j - 1);
		if (!swapped)
			break ;
		j++;
	}
	return (arr);
}

static bool	export_no_args(t_data *data, int *exit_code, t_var *env)
{
	char	**arr;
	char	**sorted_arr;
	int		size;

	arr = NULL;
	sorted_arr = NULL;
	*exit_code = 0;
	size = get_env_len(env);
	arr = list_to_arr(size, env);
	if (!arr)
	{
		*exit_code = 1;
		return (false);
	}
	sorted_arr = sort_arr_list(arr, size);
	get_export(sorted_arr, data);
	free_split(arr);
	return (true);
}

bool	ft_export(t_cmds *cmd, t_data *data, int *exit_code)
{
	t_var	*env;

	env = data->env_lst;
	if (!env)
		return (false);
	if (!cmd->cmd[1])
		return (export_no_args(data, exit_code, env));
	else
		export_with_param(cmd, data, exit_code);
	return (true);
}

