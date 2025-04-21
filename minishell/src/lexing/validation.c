#include "../includes/lexing.h"

bool	validation(t_data *data)
{
	int i;

	i = 0;

	while (data->tokens[i].data && i < data->tokens_conter)
	{
		if (data->tokens[i].type == 3
			&& data->tokens[i - 1].type == 3)
		{
			print_error("syntax error near unexpected token `|'");
			return (false);
		}
		i++;
	}

	if (data->double_quote_found || data->quote_found)
	{
		print_error("quotes are not closed");
		return (false);
	}

	/*if pipes at the end*/
	if (data->tokens[data->tokens_conter - 1].type == 3 
	|| data->tokens[data->tokens_conter - 1].type == TOK_APPEND
	|| data->tokens[data->tokens_conter - 1].type == TOK_REDIRECT_IN
	|| data->tokens[data->tokens_conter - 1].type == TOK_REDIRECT_OUT
	|| data->tokens[data->tokens_conter - 1].type == TOK_SINGLE_QUOTE
	|| data->tokens[data->tokens_conter - 1].type == TOK_DOUBLE_QUOTE)
	{
		print_error("syntax error near unexpected token");
		return (false);
	}
	
	
	return (true);
}