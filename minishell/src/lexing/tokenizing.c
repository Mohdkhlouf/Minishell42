#include "../includes/lexing.h"

/* this function to make sure from if there is a Heredoc redirection
then dont expand the variable*/


bool	empty_vars_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tokens_conter && data->tokens[i].data)
	{
		if (data->tokens[i].type == TOK_ENV_VAR
			&& data->tokens[i].data[0] == '\0')
		{
			ft_free(data->tokens[i].data);
			data->tokens[i].data = 0;
		}
		i++;
	}
	return (true);
}

bool	empty_quotes_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tokens_conter && data->tokens[i].data)
	{
		if ((data->tokens[i].type == TOK_DOUBLE_QUOTE)
			&& data->tokens[i].data[0] == '\0')
		{
			free(data->tokens[i].data);
			data->tokens[i].data = ft_strdup(" ");
			if (!data->tokens[i].data)
				return (false);
		}
		i++;
	}
	return (true);
}

bool main_tokenizing_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tokens_conter && data->tokens[i].data)
	{
		if (data->malloc_fail_flag)
			return (false);
		if (data->tokens[i].data[0] == '$')
			var_handler_token(data, i);
		else if (ft_strchr(data->tokens[i].data, '\"')
			&& ft_strchr(data->tokens[i].data, '$')
			&& data->tokens[i].data[0] != '\'')
		{
			var_handler_quotes_token(data, i);
		}
		if (!quotes_tekonizing(data, i))
			return (false);
		redirection_setting(data, i);
		i++;
	}
	return (true);
}

/*after creatiing the tokens, i start iterate them as i need, so this funnction
will solve the var$ seperated, withing quotes and then fix the qouting text to
work with double quotes and single quotes.
then i iterate the result for redirections
if the redirection is herdoc the var wis not expanded*/
bool	tokenizing(t_data *data)
{
	int	i;

	i = 0;
	if (!validation(data))
		return (false);
	if(!main_tokenizing_loop(data))
		return (false);
	if (!empty_quotes_loop(data))
		return (false);
	if (!empty_vars_loop(data))
		return (false);
	return (true);
}

