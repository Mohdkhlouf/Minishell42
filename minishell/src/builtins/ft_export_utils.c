#include "../includes/minishell.h"

void add_export_to_list(char **arr_list, t_data *data)
{
	t_var *new_export;
	t_var *temp_export = NULL;

	int i = 0;
	while (arr_list[i])
	{
		new_export = malloc(sizeof(t_var));
		if (!new_export)
			return;

		new_export->key = ft_strdup(arr_list[i]);
		new_export->value = get_env_value(arr_list[i], data);
		new_export->next = NULL;

		if (data->export_list == NULL)
			data->export_list = new_export;
		else
		{
			temp_export = data->export_list;
			while (temp_export->next)
				temp_export = temp_export->next;
			temp_export->next = new_export;
		}
		i++;
	}
}

char *get_export_value(char *key, t_data *data)
{
	t_var *export;
	export = data->export_list;
	while (export)
	{
		if (ft_strcmp(export->key, key) == 0)
			return (export->value);
		export = export->next;
	}
	export = data->new_export;
	while (export)
	{
		if (ft_strcmp(export->key, key) == 0)
			return (export->value);
		export = export->next;
	}
	return (NULL);
}

void add_new_export_var(char *key, char *value, t_data *data)
{
	t_var *add_export;
	t_var *temp = NULL;
	add_export = malloc(sizeof(t_var));
	if (!add_export)
		return;
	add_export->key = key;
	add_export->value = value;
	add_export->next = NULL;

	if (data->new_export == NULL)
		data->new_export = add_export;
	else
	{
		temp = data->new_export;
		while (temp->next)
			temp = temp->next;
		temp->next = add_export;
	}
}

void print_new_export(t_data *data)
{
	t_var *new_e = data->new_export;
	if (!data->new_export)
		return;
	while (new_e)
	{
		printf("key is: %s", new_e->key);
		printf("\n");
		new_e = new_e->next;
	}
}

void export_with_param(t_data *data)
{
	char *param_value;
	char **str;
	int i;
	int j;

	i = 0;
	j = 0;
	param_value = data->words[1];
	if (ft_isalpha(param_value[0]) || param_value[0] == '_')
	{
		if (ft_strchr(param_value, '='))
		{
			str = ft_split(param_value, '=');
			if (!str)
				return;
			while (str[i][j])
			{
				if (!ft_isalnum(str[i][j]) && str[i][j] != '_')
				{
					printf("export: \"%s\": not a valid identifier\n", param_value);
					return;
				}
				j++;
			}
			if (get_env_value(str[i], data))
				update_env_list(ft_strdup(str[i]), ft_strdup(str[i + 1]), data);
			else
				add_new_env_variable(ft_strdup(str[i]), ft_strdup(str[i + 1]), data);
		}
		else
		{
			if (!get_export_value(param_value, data))
				add_new_export_var(ft_strdup(param_value), NULL, data);
		}
	}
	else
		printf("export: \"%s\": not a valid identifier\n", param_value);
}
