#include "../includes/lexing.h"

void	split_vars_var(char *token, int *c, t_vars_data *var, int *start)
{
	while (token[*c])
	{
		if (token[*c] == '$')
		{
			var->var_is_found = true;
			if (*c != 0)
			{
				var->vars_arr[var->parts_count] = ft_substr(token, *start, *c
						- *start);
				var->parts_count++;
			}
			*start = *c;
		}
		// else if ((var->var_is_found && token[*c] == ' ') || (var->var_is_found
		// 		&& token[*c] == '/') || (var->var_is_found
		// 		&& token[*c] == '\"'))
		else if ((var->var_is_found && (ft_isalnum(token[*c]) == 0)) ||
		(var->var_is_found && (ft_isalpha(token[*c]) == 0)))
		{
			var->var_is_found = false;
			var->vars_arr[var->parts_count] = ft_substr(token, *start, *c
					- *start);
			var->parts_count++;
			*start = *c;
		}
		(*c)++;
	}
}

void	split_vars(char *token, t_vars_data *var)
{
	int	start;
	int	c;

	start = 0;
	c = 0;
	var->var_is_found = false;
	split_vars_var(token, &c, var, &start);
	if (token[c] == '\0')
	{
		if (var->var_is_found)
			var->var_is_found = false;
		if (start == c)
		{
			printf("TEST %s\n", var->vars_arr[var->parts_count]);
			var->vars_arr[var->parts_count] = ft_substr(token, start, 1);
		}		
		else
		{
			var->vars_arr[var->parts_count] = ft_substr(token, start, c
				- start);
		}
		var->parts_count++;
	}
	var->vars_arr[var->parts_count] = "\0";
}

void	var_expander(t_vars_data *var, int *c, t_data *data)
{
	(void) data;
	if (get_env_value(var->vars_arr[*c] + 1, data))
		var->vars_arr[*c] = get_env_value(var->vars_arr[*c] + 1, data);
	else
		var->vars_arr[*c] = "\0";
}

char	*expand_vars(t_vars_data *var, t_data *data)
{
	int		c;
	char	*temp;

	c = 0;
	temp = NULL;
	while (c < var->parts_count)
	{
		if (var->vars_arr[c][0] == '$')
			var_expander(var, &c, data);
		c++;
	}
	c = 0;
	while (c < var->parts_count)
	{
		if (c == 0)
		{
			temp = var->vars_arr[0];
			c++;
		}
		temp = ft_strcat(temp, var->vars_arr[c]);
		c++;
	}
	return (temp);
}

bool	var_handler2(t_data *data, int i)
{
	t_vars_data	*var;

	var = ft_calloc(1, sizeof(t_vars_data));
	if (!var)
		return (free(var), false);
	if (!var_init(var, data, i))
		return (free(var), false);
	split_vars(data->tokens[i].data, var);
	var->var_var = expand_vars(var, data);
	path_set_and_join(data, i, var->temp, var->var_var);
	// free(var->var_var);
	free_var(var);
	return (true);
}
