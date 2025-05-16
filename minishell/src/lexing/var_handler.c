#include "../includes/lexing.h"

void	process_add(t_vars_data *var, char *temp)
{
	var->vars_arr[var->parts_count] = ft_strdup(temp); //segfault
	ft_free(temp);
	var->parts_count++;
}

void	split_vars_var(char *token, int *c, t_vars_data *var, int *start)
{
	char	*temp;

	while (token[*c])
	{
		temp = NULL;
		if (token[*c] == '$')
		{
			var->var_is_found = true;
			if (*c != 0)
			{
				temp = ft_substr(token, *start, *c - *start);
				process_add(var, temp);
			}
			*start = *c;
		}
		else if (token[*c] == '?' && token[*c - 1] == '$')
		{
			var->var_is_found = false;
			temp = ft_substr(token, *start, 2);
			process_add(var, temp);
			*start = *c + 1;
		}
		else if (*c > 0 && (token[*c - 1] == '$')
			&& ((ft_isdigit(token[*c]) == 1) && (ft_isdigit(token[*c
						+ 1]) == 1)))
		{
			var->var_is_found = false;
			temp = ft_substr(token, *start, 2);
			process_add(var, temp);
			*start = *c + 1;
		}
		else if (var->var_is_found && (ft_isalnum(token[*c]) == 0))
		{
			var->var_is_found = false;
			temp = ft_substr(token, *start, *c - *start);
			process_add(var, temp);
			*start = *c;
		}
		(*c)++;
	}
	// free(temp);
}

void	split_vars(char *token, t_vars_data *var)
{
	int	start;
	int	c;

	var->temp = NULL;
	start = 0;
	c = 0;
	var->var_is_found = false;
	split_vars_var(token, &c, var, &start);
	if (token[c] == '\0')
	{
		var->var_is_found = false;
		if (start == c)
			var->temp = ft_substr(token, start, 1);
		else
			var->temp = ft_substr(token, start, c - start);
		var->vars_arr[var->parts_count] = ft_strdup(var->temp); // segfault
		var->parts_count++;
	}
	var->vars_arr[var->parts_count] = NULL;
}

void	var_expander(t_vars_data *var, int *c, t_data *data)
{
	char	*env_value;

	env_value = NULL;
	if ((var->vars_arr[*c][1]) == '?')
	{
		free(var->vars_arr[*c]);
		var->vars_arr[*c] = NULL;
		var->vars_arr[*c] = ft_itoa(data->exit_code);
		return ;
	}
	env_value = get_env_value(var->vars_arr[*c] + 1, data);
	if (env_value)
	{
		free(var->vars_arr[*c]);
		var->vars_arr[*c] = NULL;
		var->vars_arr[*c] = ft_strdup(env_value);
	}
	else
	{
		free(var->vars_arr[*c]);
		// var->vars_arr[*c] = ft_strdup("");
		var->vars_arr[*c] = 0;
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
	while (c < var->parts_count)
	{
		if (var->vars_arr[c][0] == '$' && var->vars_arr[c][1])
			var_expander(var, &c, data);
		c++;
	}
	c = 0;
	while (c < var->parts_count)
	{
		if(!var->vars_arr[0])
			return (NULL);
		if (!joined)
			joined = ft_strdup(var->vars_arr[0]);
		else
		{
			temp = joined;
			joined = ft_strjoin(temp, var->vars_arr[c]);
			free(temp);
		}
		c++;
	}
	return (joined);
}

void	path_set_and_join(t_data *data, int i, t_vars_data *var)
{
	if (var->var_var == NULL)
	{
		free(data->tokens[i].data);
		data->tokens[i].data = NULL;
		// exit(EXIT_FAILURE);
	}
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
	len = 0;
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
	split_vars(data->tokens[i].data, var);
	var->var_var = expand_vars(var, data);
	path_set_and_join(data, i, var);
	free(var->temp);
	free_var(var);
	return (true);
}
