#include "../../includes/minishell.h"

// TODO return value

void get_export(char **sorted_arr, t_data *data)
{
	int i;

	i = 0;
	while (sorted_arr[i])
	{
		printf("declare -x %s", sorted_arr[i]);
		if (get_env_value(sorted_arr[i], data) && get_env_value(sorted_arr[i],
																data)[0] != '\0')
		{
			printf("=\"%s\"", get_env_value(sorted_arr[i], data));
		}
		printf("\n");
		i++;
	}
}

int get_env_len(t_var *env)
{
	int count;

	count = 0;
	if (!env)
		return (-1);
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char **list_to_arr(int size, t_var *env)
{
	char **arr_str;
	int i;

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

char **sort_arr_list(char **arr, int size)
{
	int j;
	int swapped;
	char *temp;
	int k;

	j = 0;
	while (j < size - 1)
	{
		swapped = 0;
		k = 0;
		while (k < size - j - 1)
		{
			if (ft_strcmp(arr[k], arr[k + 1]) > 0)
			{
				temp = arr[k];
				arr[k] = arr[k + 1];
				arr[k + 1] = temp;
				swapped = 1;
			}
			k++;
		}
		if (!swapped)
			break;
		j++;
	}
	return (arr);
}

bool ft_export(t_cmds *cmd, t_data *data, int *exit_code)
{
	char **arr;
	char **sorted_arr;
	int size;
	t_var *env;

	arr = NULL;
	sorted_arr = NULL;
	size = 0;
	env = data->env_lst;
	if (!env)
		return (false);
	if (!cmd->cmd[1])
	{
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
	}
	else
		export_with_param(cmd, data, exit_code);
	// free(arr);
	return (true);
}

// int ft_export(t_data *data)
// {
// 	char **arr;
// 	char **sorted_arr;
// 	int size;
// 	t_var *env;

// 	arr = NULL;
// 	sorted_arr = NULL;
// 	size = 0;
// 	env = data->env_lst;
// 	if (!env)
// 		return (1);

// 	if (!data->words[1])
// 	{
// 		size = get_env_len(env);
// 		arr = list_to_arr(size, env);
// 		if (!arr)
// 			return (1);
// 		sorted_arr = sort_arr_list(arr, size);
// 		get_export(sorted_arr, data);
// 	}
// 	else
// 		export_with_param(data);
// 	free(arr);
// 	return (0);
// }

// add_export_to_list(sorted_arr, data);
// print_export(data);
// void print_export(t_data *data)
// {
// 	t_var *export_node;
// 	if (!data->export_list)
// 	{
// 		printf("Error: No environment variables to export.\n");
// 		return ;
// 	}
// 	export_node = data->export_list;
// 	while (export_node)
// 	{
// 		printf("\033[0;32mdeclare -x %s", export_node->key);
// 		if (export_node->value && export_node->value[0] != '\0')
// 		{
// 			printf("\033[0;32m=\"%s\"", export_node->value);
// 		}
// 		printf("\033[0m\n");
// 		export_node = export_node->next;
// 	}
// }
