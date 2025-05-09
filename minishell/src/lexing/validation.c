#include "../includes/lexing.h"

bool	validation(t_data *data)
{
	int i;

	i = 0;
	if (data->tokens_conter == 1)
		return (true);
	while (data->tokens[i].data && i < data->tokens_conter)
	{
		if (data->tokens[0].type == 3)
			{
			print_error("syntax error near unexpected token `|'");
			data->exit_code = 2;
			return (false);
		}
		if (data->tokens[i].type == 3
			&& data->tokens[i + 1].type == 3)
		{
			print_error("syntax error near unexpected token `|'");
			data->exit_code = 2;
			return (false);
		}

		if ((data->tokens[i].type == TOK_REDIRECT_IN 
		|| data->tokens[i].type == TOK_REDIRECT_OUT
		|| data->tokens[i].type == TOK_REDIRECT_HEREDOC
		|| data->tokens[i].type == TOK_APPEND) &&
		data->tokens[i + 1].type == 3)
		{
			print_error("syntax error near unexpected token `|'");
			data->exit_code = 2;
			return (false);
		}
		i++;
	}

	if (data->quote_found && data->first_quote_type == 1)
	{
		print_error("quotes are not closed");
		data->exit_code = 2;
		return (false);
	}

	if (data->double_quote_found && data->first_quote_type == 2)
	{
		print_error("quotes are not closed");
		data->exit_code = 2;
		return (false);
	}
	return (true);
}