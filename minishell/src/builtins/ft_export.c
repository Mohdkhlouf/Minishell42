#include "../includes/minishell.h"

// TODO return value

int get_env_len(t_var *env)
{
	int count = 0;
	if (!env)
		return (0);
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
	int i = 0;

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
	int j = 0;
	int swapped;
	char *temp;

	while (j < size - 1)
	{
		swapped = 0;
		int k = 0;
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
void get_export(char **sorted_arr, t_data *data)
{
	int i = 0;
	while (sorted_arr[i])
	{
		printf("declare -x %s", sorted_arr[i]);
		if (get_env_value(sorted_arr[i], data) && get_env_value(sorted_arr[i], data)[0] != '\0')
		{
			printf("=\"%s\"", get_env_value(sorted_arr[i], data));
		}
		printf("\n");
		i++;
	}
}

int ft_export(t_data *data)
{
	char **arr = NULL;
	char **sorted_arr = NULL;

	int size = 0;

	t_var *env = data->env_lst;
	if (!env)
		return (1);
	size = get_env_len(env);
	if (!data->words[1])
	{
		arr = list_to_arr(size, env);
		if (!arr)
			return (1);
		sorted_arr = sort_arr_list(arr, size);
		get_export(sorted_arr, data);
	}
	else
		export_with_param(data);
	// TODO free arr
	return (0);
}
