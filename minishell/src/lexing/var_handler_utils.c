#include "../includes/lexing.h"


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
	var->temp = NULL;
	var->var_var = NULL;
	var->vars_arr = NULL;
	var->parts_count = 0;
	var->vars_count = 0;
	var->len = ft_strlen(data->tokens[i].data);
	var->vars_count = find_vars_count(data, i);
	var->vars_arr = ft_calloc((var->len), sizeof(char *));
	if (!var->vars_arr)
		return (free (var->vars_arr ), false);
	return (true);
}

void	search_for_file_seperator(t_data *data, t_var_d *var, int i)
{
	while (var->j < var->len)
	{
	
		if (data->tokens[i].data[0] == '$')
			var->j++;
		if(ft_isalnum(data->tokens[i].data[var->j]) == 0 && ft_isalpha(data->tokens[i].data[var->j]) == 0 )
		{
			data->file_seperator_found = true;
			break ;
		}
		var->j++;
	}
}

void	path_set_and_join(t_data *data, int i, char *temp, char *path)
{
	if (path == NULL)
		exit(EXIT_FAILURE);
	else
	{
		if (data->file_seperator_found == true)
			{
				free(data->tokens[i].data);
				data->tokens[i].data = ft_strdup(ft_strcat(path, temp));
			}
		else {
			free(data->tokens[i].data);
			data->tokens[i].data = ft_strdup(path);
		}
		data->tokens[i].type = TOK_ENV_VAR;
	}
}



void	print_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i].data && i<data->tokens_conter)
	{
		printf("Token:#%s# Type:%u\n", data->tokens[i].data,
			data->tokens[i].type);
		i++;
	}
}

void	free_var_handler(t_data *data,t_vars_data *var)
{
	if (!var)
		return;
	(void) data;
	// if (var->vars_arr)
	// {
	// 	for (int i = 0; i < data->tokens_conter; i++)
	// 		free(var->vars_arr[i]);  // 🔥 This is the key fix
	// }
	free(var->temp);
	free(var->var_var);
	free(var);
}