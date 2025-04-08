#include "../includes/lexing.h"

void	assign_quotes(t_data *data, int len, int i, char *temp)
{
	int	c;
	int	j;

	c = 0;
	j = 0;
	while (j < len)
	{
		if (data->tokens[i].data[j] == '\'' && data->quote_type == 0)
			data->quote_type = '\'';
		if (data->tokens[i].data[j] == '\"' && data->quote_type == 0)
			data->quote_type = '\"';
		if (data->tokens[i].data[j] == data->quote_type
			|| (data->tokens[i].data[j] == '\'' && data->quote_type == 0)
				|| (data->tokens[i].data[j] == '\"' && data->quote_type == 0))
			j++;
		else
		{
			temp[c] = data->tokens[i].data[j];
			c++;
			j++;
		}
	}
	data->quote_type = 0;
	temp[c] = '\0';
}

void	quote_fixing(t_data *data, int i)
{
	char	*temp;
	int		len;

	if (data->tokens[i].data[0] == '\'')
		data->tokens[i].type = TOK_SINGLE_QUOTE;
	else if (data->tokens[i].data[0] == '\"')
		data->tokens[i].type = TOK_DOUBLE_QUOTE;
	len = ft_strlen(data->tokens[i].data);
	temp = malloc(sizeof(char) * len + 1);
	if (!temp)
		exit(EXIT_FAILURE);
	assign_quotes(data, len, i, temp);
	free(data->tokens[i].data);
	data->tokens[i].data = ft_strdup(temp);
	free(temp);
}
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
	t_var_d *var;
	
	var = malloc (sizeof (t_var_d));
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
	if (getenv(var->var + 1))
		var->path = ft_strdup(getenv(var->var + 1));
	else
		var->path = ft_strdup("");
	path_set_and_join(data, i, var->temp, var->path);
	free_var_mem(var);
}

void	redirection_setting(t_data *data, int i)
{
	if (data->tokens[i].type == TOK_UNKNOWN && i > 0)
	{
		if (data->tokens[i - 1].type == TOK_REDIRECT_IN && data->tokens[i
			- 1].data[0] == '<')
			data->tokens[i].type = TOK_REDIRECT_IN;
		else if (data->tokens[i - 1].type == TOK_REDIRECT_OUT && data->tokens[i
			- 1].data[0] == '>')
			data->tokens[i].type = TOK_REDIRECT_OUT;
		else if (data->tokens[i - 1].type == TOK_APPEND && data->tokens[i
			- 1].data[0] == '>')
			data->tokens[i].type = TOK_APPEND;
		else if (data->tokens[i - 1].type == TOK_REDIRECT_HEREDOC
			&& data->tokens[i - 1].data[0] == '<')
			data->tokens[i].type = TOK_REDIRECT_HEREDOC;
	}
}
/* this function to make sure from if there is a Heredoc redirection 
then dont expand the variable*/
void init_var_handler(t_data *data, int *i)
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
	while (i < data->tokens_conter)
	{
		if (data->tokens[i].data[0] == '$')
		{
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
