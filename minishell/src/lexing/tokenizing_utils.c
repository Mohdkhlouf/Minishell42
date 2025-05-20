#include "../includes/lexing.h"

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

bool	set_exit_value(t_data *data, int i)
{
	if (data->tokens[i].data)
		free(data->tokens[i].data);
	data->tokens[i].data = ft_itoa(data->exit_code);
	if (!data->tokens[i].data)
		return (false);
	return (true);
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

bool	var_handler_token(t_data *data, int i)
{
	if (data->tokens[i].data[1] == '?' && !data->tokens[i].data[2])
	{
		if (!set_exit_value(data, i))
			return (false);
	}
	else
	{
		if (!init_var_handler(data, &i))
			return (false);
	}
	return (true);
}

bool	quotes_tekonizing(t_data *data, int i)
{
	if (data->tokens[i].data && (ft_strchr(data->tokens[i].data, '\'')
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
