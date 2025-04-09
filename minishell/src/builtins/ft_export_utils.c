#include "../includes/minishell.h"

char *get_env_key(char *key, t_data *data)
{
	t_var *env;

	env = data->env_lst;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0 && (ft_strlen(env->key) == ft_strlen(key)))
			return (env->key);
		env = env->next;
	}
	return (NULL);
}

void has_equal_sign(char *param_value, t_data *data)
{
	char **str;
	int j;

	j = 0;
	str = ft_split(param_value, '=');
	if (!str)
		return;
	while (str[0][j])
	{
		if (!ft_isalnum(str[0][j]) && str[0][j] != '_')
		{
			printf("export: \"%s\": not a valid identifier\n", param_value);
			return;
		}
		j++;
	}
	if (get_env_key(str[0], data))
		update_env_list(ft_strdup(str[0]), ft_strdup(str[1]), data);
	else
		add_new_env_variable(ft_strdup(str[0]), ft_strdup(str[1]), data);
}

void export_with_param(t_data *data)
{
	char *param_value;
	
	param_value = data->words[1];
	if (ft_isalpha(param_value[0]) || param_value[0] == '_')
	{
		if (ft_strchr(param_value, '='))
			has_equal_sign(param_value, data);
		else
		{
			if (get_env_key(param_value, data))
				update_env_list(ft_strdup(param_value), NULL, data);
			else
				add_new_env_variable(ft_strdup(param_value), NULL, data);
		}
	}
	else
		printf("export: \"%s\": not a valid identifier\n", param_value);
}


// void add_export_to_list(char **arr_list, t_data *data)
// {
// 	t_var *new_export;
// 	t_var *temp_export = NULL;

// 	int i = 0;
// 	while (arr_list[i])
// 	{
// 		new_export = malloc(sizeof(t_var));
// 		if (!new_export)
// 			return;

// 		new_export->key = ft_strdup(arr_list[i]);
// 		new_export->value = get_env_value(arr_list[i], data);
// 		new_export->next = NULL;

// 		if (data->export_list == NULL)
// 			data->export_list = new_export;
// 		else
// 		{
// 			temp_export = data->export_list;
// 			while (temp_export->next)
// 				temp_export = temp_export->next;
// 			temp_export->next = new_export;
// 		}
// 		i++;
// 	}
// }