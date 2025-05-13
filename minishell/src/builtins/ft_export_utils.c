#include "../includes/minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

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

static bool	validate_and_store_env(char **str, char *param_value, t_data *data)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (str[0][i])
	{
		if (!ft_isalnum(str[0][i]) && str[0][i] != '_')
		{
			minishell_error("export", "not a valid identifier", param_value);
			return (false);
		}
		i++;
	}
	key = ft_strdup(str[0]);
	if (!key)
		return (false);
	value = str[1] ? ft_strdup(str[1]) : ft_strdup("");
	if (!value)
	{
		free(key);
		return (false);
	}
	if (get_env_key(key, data))
		update_env_list(key, value, data);
	else
		add_new_env_variable(key, value, data);
	free(key);
	free(value);
	return (true);
}

static void	has_equal_sign(char *param_value, t_data *data, bool *invalid_found)
{
	char	**str;

	*invalid_found = false;
	str = ft_split(param_value, '=');
	if (!str)
		return ;
	if (!validate_and_store_env(str, param_value, data))
		*invalid_found = true;
	free_split(str);
}

static void	handle_valid_export_param(char *param_value, t_data *data,
		bool *invalid_found)
{
	char	*temp;
	char *copy_param_val;

	temp = NULL;
	if (ft_strchr(param_value, '='))
		has_equal_sign(param_value, data, invalid_found);
	else
	{
		if (get_env_key(param_value, data))
		{
			temp = ft_strdup(param_value);
			update_env_list(temp, NULL, data);
		}
		else
		{
			copy_param_val = ft_strdup(param_value);
			if(copy_param_val)
			{
				add_new_env_variable(copy_param_val, NULL, data);
				free(copy_param_val);
			}
			else	
				return;
		}
	}
	free(temp);
}

void	export_with_param(t_cmds *cmd, t_data *data, int *exit_code)
{
	int		i;
	bool	invalid_found;
	char	*param_value;

	i = 1;
	invalid_found = false;
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
