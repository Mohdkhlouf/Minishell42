#include "../includes/lexing.h"

void	var_init(t_vars_data *var, t_data *data, int i)
{
	var->len = 0;
	var->temp = NULL;
	var->var_var = NULL;
	var->vars_arr = NULL;
	var->parts_count = 0;
	var->vars_count = 0;
	var->len = ft_strlen(data->tokens[i].data);
	var->vars_count = find_vars_count(data, i);
	var->vars_arr = (char **)malloc(sizeof(char *) * (var->vars_count * 20));
	if (!var->vars_arr)
		exit(EXIT_FAILURE);
}

void	search_for_file_seperator(t_data *data, int i, int len, int *j)
{
	while (*j < len)
	{
		if (data->tokens[i].data[*j] == '/' || data->tokens[i].data[*j] == '\''
			|| data->tokens[i].data[*j] == '\"')
		{
			data->file_seperator_found = true;
			break ;
		}
		(*j)++;
	}
}

void	path_set_and_join(t_data *data, int i, char *temp, char *path)
{
	if (path == NULL)
		exit(EXIT_FAILURE);
	else
	{
		if (data->file_seperator_found == true)
			data->tokens[i].data = ft_strdup(ft_strcat(path, temp));
		else
			data->tokens[i].data = ft_strdup(path);
		data->tokens[i].type = TOK_ENV_VAR;
	}
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

void	print_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tokens_conter)
	{
		printf("Token:#%s# Type:%u\n", data->tokens[i].data,
			data->tokens[i].type);
		i++;
	}
}
