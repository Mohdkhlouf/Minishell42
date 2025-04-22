#include "../includes/lexing.h"

void	init_var(t_var_d *var, t_data *data, int i)
{
	var->temp = NULL;
	var->var = NULL;
	var->path = NULL;
	var->j = 0;
	var->len = ft_strlen(data->tokens[i].data);
}

void	free_var_mem(t_var_d *var)
{
	free(var->var);
	free(var->temp);
	free(var->path);
	free(var);
}

void	var_handler(t_data *data, int i)
{
	t_var_d	*var;

	var = ft_calloc(1, sizeof(t_var_d));
	if (!var)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	init_var(var, data, i);
	search_for_file_seperator(data, var, i);
	if (data->file_seperator_found)
	{
		var->var = ft_substr(data->tokens[i].data, 0, var->j);
		var->temp = ft_substr(data->tokens[i].data, var->j, var->len);
	}
	else
		var->var = data->tokens[i].data;
	if (get_env_value(var->var + 1, data))
		var->path = ft_strdup(get_env_value(var->var + 1, data));
	else
		var->path = ft_strdup("");
	path_set_and_join(data, i, var->temp, var->path);
	free_var_mem(var);
}

/* this function to make sure from if there is a Heredoc redirection
then dont expand the variable*/
void	init_var_handler(t_data *data, int *i)
{
	if (data->tokens_conter > 1)
	{
		if (*i > 0 && data->tokens[*i - 1].type == TOK_REDIRECT_HEREDOC)
			data->tokens[*i].type = TOK_REDIRECT_HEREDOC;
		else
			var_handler(data, *i);
	}
	else
		var_handler(data, *i);
}


/*after creatiing the tokens, i start iterate them as i need, so this funnction
will solve the var$ seperated, withing quotes and then fix the qouting text to
work with double quotes and single quotes.
then i iterate the result for redirections
if the redirection is herdoc the var wis not expanded*/
int	tokenizing(t_data *data)
{
	int	i;

	i = 0;
	if (!validation(data))
		return (FAILIURE);
	while (i < data->tokens_conter)
	{
		if (data->tokens[i].data[0] == '$')
		{
			if (data->tokens[i].data[1] == '?' && !data->tokens[i].data[2])
			{
				data->tokens[i].data = ft_itoa(g_exit_status);
			}
			else
				init_var_handler(data, &i);
		}
		// else if ((data->tokens[i].data[0] == '\"')
		// 	&& ft_strchr(data->tokens[i].data, '$'))
		// 	var_handler2(data, i);
		else if (ft_strchr(data->tokens[i].data, '\"')
			&& ft_strchr(data->tokens[i].data, '$'))
			var_handler2(data, i);
		if (ft_strchr(data->tokens[i].data, '\'')
				|| ft_strchr(data->tokens[i].data, '\"'))
			quote_fixing(data, i);
		redirection_setting(data, i);
		i++;
	}
	print_tokens(data);
	return (SUCCESS);
}
