#include "../includes/lexing.h"

void	var_expander(t_vars_data *var, int *c, t_data *data)
{
	char	*env_value;

	env_value = NULL;
	if ((var->vars_arr[*c][1]) == '?')
	{
		free(var->vars_arr[*c]);
		var->vars_arr[*c] = NULL;
		var->vars_arr[*c] = ft_itoa(data->exit_code);
		if (!var->vars_arr[*c])
			data->malloc_fail_flag = true;
		return ;
	}
	env_value = get_env_value(var->vars_arr[*c] + 1, data);
	if (env_value)
	{
		free(var->vars_arr[*c]);
		var->vars_arr[*c] = ft_strdup(env_value);
	}
	else
	{
		free(var->vars_arr[*c]);
		var->vars_arr[*c] = ft_strdup("");
	}
	if (!var->vars_arr[*c])
		data->malloc_fail_flag = true;
}

void	loop_to_expand(t_vars_data *var, t_data *data)
{
	int	c;

	c = 0;
	while (c < var->parts_count)
	{
		if (data->malloc_fail_flag)
		{
			command_cleanup(data, data->cmds_d);
			exit(1);
		}
		if (var->vars_arr[c][0] == '$' && var->vars_arr[c][1])
			var_expander(var, &c, data);
		c++;
	}
}

char	*expand_vars(t_vars_data *var, t_data *data)
{
	int		c;
	char	*temp;
	char	*joined;

	c = 0;
	temp = NULL;
	joined = NULL;
	loop_to_expand(var, data);
	while (c < var->parts_count)
	{
		if (data->malloc_fail_flag)
		{
			command_cleanup(data, data->cmds_d);
			exit(1);
		}
		if (!joined)
			joined = ft_strdup(var->vars_arr[0]);
		else
		{
			temp = joined;
			joined = ft_strjoin(temp, var->vars_arr[c]);
			free(temp);
		}
		if (!joined)
			data->malloc_fail_flag = true;
		c++;
	}
	return (joined);
}

void	path_set_and_join(t_data *data, int i, t_vars_data *var)
{
	if (var->var_var == NULL)
		exit(EXIT_FAILURE);
	else
	{
		free(data->tokens[i].data);
		data->tokens[i].data = ft_strdup(var->var_var);
	}
	data->tokens[i].type = TOK_ENV_VAR;
}

bool	var_handler2(t_data *data, int i)
{
	t_vars_data	*var;
	int			len;
	int			j;

	j = 0;
	len = ft_strlen(data->tokens[i].data);
	while (j < len)
	{
		if (data->tokens[i].data[j] == '$' && (data->tokens[i].data[j
				+ 1] == '\"' || data->tokens[i].data[j + 1] == '\0'))
			return (true);
		j++;
	}
	var = ft_calloc(1, sizeof(t_vars_data));
	if (!var)
		return (free(var), false);
	if (!var_init(var, data, i))
		return (free(var), false);
	split_vars(data, data->tokens[i].data, var);
	var->var_var = expand_vars(var, data);
	path_set_and_join(data, i, var);
	free(var->temp);
	free_var(var);
	return (true);
}
