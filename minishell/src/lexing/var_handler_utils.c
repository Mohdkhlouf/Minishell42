#include "../includes/lexing.h"

void	free_var(t_vars_data *var)
{
	int	i;

	i = 0;
	while (i < var->parts_count)
	{
		if (var->vars_arr[i] != NULL)
		{
			free(var->vars_arr[i]);
			var->vars_arr[i] = NULL;
		}
		i++;
	}
	free(var->vars_arr);
	var->vars_arr = NULL;
	ft_free(var->var_var);
	free(var);
}

int	find_vars_count(t_data *data, int i)
{
	int	j;
	int	vars_count;

	j = 0;
	vars_count = 0;
	while (data->tokens[i].data[j])
	{
		if (data->tokens[i].data[j] == '$')
			vars_count++;
		j++;
	}
	return (vars_count);
}

bool	var_init(t_vars_data *var, t_data *data, int i)
{
	var->len = 0;
	var->var_var = NULL;
	var->vars_arr = NULL;
	var->parts_count = 0;
	var->vars_count = 0;
	var->len = ft_strlen(data->tokens[i].data);
	var->vars_count = find_vars_count(data, i);
	var->vars_arr = ft_calloc((var->len), sizeof(char *));
	if (!var->vars_arr)
		return (free(var->vars_arr), false);
	var->var_malloc_flag = false;
	return (true);
}

void	search_for_file_seperator(t_data *data, t_var_d *var, int i)
{
	while (var->j < var->len)
	{
		if (data->tokens[i].data[0] == '$')
			var->j++;
		if (ft_isalnum(data->tokens[i].data[var->j]) == 0
			&& ft_isalpha(data->tokens[i].data[var->j]) == 0)
		{
			data->file_seperator_found = true;
			break ;
		}
		var->j++;
	}
}

bool	split_vars(t_data *data, char *token, t_vars_data *var)
{
	var->temp = NULL;
	var->start = 0;
	var->c = 0;
	var->var_is_found = false;
	if (!split_vars_var(token, var))
		return (false);
	if (token[var->c] == '\0')
	{
		var->var_is_found = false;
		if (var->start == var->c)
			var->temp = ft_substr(token, var->start, 1);
		else
			var->temp = ft_substr(token, var->start, var->c - var->start);
		if (!var->temp)
			return (false);
		var->vars_arr[var->parts_count] = ft_strdup(var->temp);
		if (!var->vars_arr[var->parts_count])
			return (false);
		var->parts_count++;
	}
	var->vars_arr[var->parts_count] = NULL;
	return (true);
}
