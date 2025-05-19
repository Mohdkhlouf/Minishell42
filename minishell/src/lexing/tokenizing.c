#include "../includes/lexing.h"

/* this function to make sure from if there is a Heredoc redirection
then dont expand the variable*/
bool	init_var_handler(t_data *data, int *i)
{
	if (data->tokens_conter > 1)
	{
		if (*i > 0 && data->tokens[*i - 1].type == TOK_REDIRECT_HEREDOC)
			data->tokens[*i].type = TOK_REDIRECT_HEREDOC;
		else if (!var_handler2(data, *i))
			return (false);
	}
	else if (!var_handler2(data, *i))
		return (false);
	return (true);
}

void	set_exit_value(t_data *data, int i)
{
	if (data->tokens[i].data)
		free(data->tokens[i].data);
	data->tokens[i].data = ft_itoa(data->exit_code);
}

void	var_handler_quotes_token(t_data *data, int i)
{
	if (data->tokens_conter > 1 && i != 0)
	{
		if (!ft_strnstr(data->tokens[i - 1].data, "<<", 2))
			var_handler2(data, i);
	}
	else
		var_handler2(data, i);
}

void	var_handler_token(t_data *data, int i)
{
	if (data->tokens[i].data[1] == '?' && !data->tokens[i].data[2])
		set_exit_value(data, i);
	else
		init_var_handler(data, &i);
}

bool	quotes_tekonizing(t_data *data, int i)
{
	if ((ft_strchr(data->tokens[i].data, '\'')
				|| ft_strchr(data->tokens[i].data, '\"')))
	{
		if (!(i > 0 && (data->tokens[i - 1].data) && ft_strnstr(data->tokens[i
					- 1].data, "<<", 2)))
		{
			if (!quote_fixing(data, i))
				return (false);
		}
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
	// print_tokens(data);
	if (!validation(data))
		return (false);
	while (i < data->tokens_conter && data->tokens[i].data)
	{
		if (data->malloc_fail_flag)
			{
				command_cleanup(data, data->cmds_d);
				exit(1);
			}
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
	i = 0;
	while (i < data->tokens_conter && data->tokens[i].data)
	{
		if ((data->tokens[i].type == TOK_DOUBLE_QUOTE)  && data->tokens[i].data[0] == '\0')
		{
			free(data->tokens[i].data);
			data->tokens[i].data = ft_strdup(" ");
		}
		i++;
	}

	i = 0;
	while (i < data->tokens_conter && data->tokens[i].data)
	{
		if (data->tokens[i].type == TOK_ENV_VAR && data->tokens[i].data[0] == '\0')
		{
			ft_free(data->tokens[i].data);
			data->tokens[i].data = 0;
		}
		i++;
	}
	// print_tokens(data);
	return (true);
}


void	print_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i].data && i < data->tokens_conter)
	{
		printf("Token:#%s# Type:%u\n", data->tokens[i].data,
			data->tokens[i].type);
		i++;
	}
}