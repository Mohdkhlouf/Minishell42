#include "../includes/minishell.h"

static int is_valid_identifier(const char *str)
{
	int i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static bool validate_and_store_env(char **str, char *param_value, t_data *data)
{
	int i;
	char *key;
	char *value;

	i = 0;
	while (str[0][i])
	{
		if (!ft_isalnum(str[0][i]) && str[0][i] != '_')
		{
			minishell_error("export", "not a valid identifier", param_value);
			return false;
		}
		i++;
	}
	key = ft_strdup(str[0]);
	value = str[1] ? ft_strdup(str[1]) : ft_strdup("");
	if (get_env_key(key, data))
		update_env_list(key, value, data);
	else
		add_new_env_variable(key, value, data);
	return (true);
}

static void has_equal_sign(char *param_value, t_data *data, bool *invalid_found)
{
	char **str;

	*invalid_found = false;
	str = ft_split(param_value, '=');
	if (!str)
		return;
	if (!validate_and_store_env(str, param_value, data))
		*invalid_found = true;

	free_split(str);
}

static void handle_valid_export_param(char *param_value, t_data *data, bool *invalid_found)
{
	if (ft_strchr(param_value, '='))
		has_equal_sign(param_value, data, invalid_found);
	else
	{
		if (get_env_key(param_value, data))
			update_env_list(ft_strdup(param_value), NULL, data);
		else
			add_new_env_variable(ft_strdup(param_value), NULL, data);
	}
}

void export_with_param(t_cmds *cmd, t_data *data, int *exit_code)
{
	int i = 1;
	bool invalid_found = false;
	char *param_value;

	while (cmd->cmd[i])
	{
		param_value = cmd->cmd[i];
		if (is_valid_identifier(param_value))
			handle_valid_export_param(param_value, data, &invalid_found);
		else
		{
			minishell_error("export", "not a valid identifier", param_value);
			invalid_found = true;
		}
		i++;
	}
	if (invalid_found)
		*exit_code = 1;
}

// if (str[1])
// value = ft_strdup(str[1]);
// else
// value = ft_strdup("");
// ft_putstr_fd("minishell: export: `", 2);
// ft_putstr_fd(param_value, 2);
// ft_putstr_fd("': not a valid identifier\n", 2);
// void add_export_to_list(char **arr_list, t_data *data)
// {
// 	t_var *new_export;
// 	t_var *temp_export = NULL;

// 	int i = 0;
// 	while (arr_list[i])
// 	{
// 		new_export = malloc(sizeof(t_var));
// 		if (!new_export)
// 			return ;

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
// ft_putstr_fd("minishell: export: `", 2);
// ft_putstr_fd(param_value, 2);
// ft_putstr_fd("': not a valid identifier\n", 2);
// while (str[0][j])
// {
// 	if (!ft_isalnum(str[0][j]) && str[0][j] != '_')
// 	{
// 		*invalid_found = true;
// 		minishell_error("export", "not a valid identifier", param_value);
// 		free_split(str);
// 		return;
// 	}
// 	j++;
// }
// key = ft_strdup(str[0]);
// value = str[1] ? ft_strdup(str[1]) : ft_strdup("");
// if (get_env_key(str[0], data))
// 	update_env_list(key, value, data);
// else
// 	add_new_env_variable(key, value, data);
// int j;
// char *key;
// char *value;

// j = 0;
