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
		else if ((var->var_is_found && token[*c] == ' ') || (var->var_is_found
				&& token[*c] == '/') || (var->var_is_found
				&& token[*c] == '\"'))
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
			var->vars_arr[var->parts_count] = ft_substr(token, start, 1);
		else
			var->vars_arr[var->parts_count] = ft_substr(token, start, c
					- start);
		var->parts_count++;
		var->vars_arr[var->parts_count] = ft_strdup("\0");
	}
}

void	var_expander(t_vars_data *var, int *c)
{
	if (getenv(var->vars_arr[*c] + 1))
		var->vars_arr[*c] = ft_strdup(getenv(var->vars_arr[*c] + 1));
	else
		var->vars_arr[*c] = ft_strdup("");
}

char	*expand_vars(t_vars_data *var)
{
	int		c;
	char	*temp;

	c = 0;
	temp = NULL;
	while (c < var->parts_count)
	{
		if (var->vars_arr[c][0] == '$')
			var_expander(var, &c);
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
		temp = ft_strdup(ft_strcat(temp, var->vars_arr[c]));
		c++;
	}
	return (temp);
}

void	free_var(t_vars_data *var)
{
	free(var->vars_arr);
	free(var);
}

void	var_handler2(t_data *data, int i)
{
	t_vars_data	*var;

	var = malloc(sizeof(t_vars_data) * 1);
	if (!var)
		exit(EXIT_FAILURE);
	var_init(var, data, i);
	split_vars(data->tokens[i].data, var);
	var->var_var = expand_vars(var);
	path_set_and_join(data, i, var->temp, var->var_var);
	free_var(var);
}
