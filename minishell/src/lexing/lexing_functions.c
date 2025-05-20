#include "../includes/lexing.h"

// this one to add the data for double operators,
// i have to make it + 1 to make it prints the second letter.
void	append_token_double(t_data *data, int type)
{
	if (data->end == data->start)
		data->tokens[data->tokens_conter].data = ft_substr(data->input_line,
				data->start, 1);
	else
		data->tokens[data->tokens_conter].data = ft_substr(data->input_line,
				data->start, data->end - data->start + 1);
	if (!data->tokens[data->tokens_conter].data )
	{
		command_cleanup(data, data->cmds_d);
		exit(1);
	}
	data->tokens[data->tokens_conter].type = type;
	data->tokens_conter++;
}

/*this functton add outfile redirection with appened*/
void	redirectout_function(t_data *data)
{
	if (data->in_token)
	{
		append_token(data, TOK_UNKNOWN);
		data->in_token = false;
	}
	data->start = data->end;
	if (data->input_line[data->end + 1] == '>')
	{
		data->end++;
		append_token_double(data, TOK_APPEND);
	}
	else
		append_token(data, TOK_REDIRECT_OUT);
	data->start = data->end + 1;
}

/*this functton add input redirection with herdoc*/
void	redirectin_function(t_data *data)
{
	if (data->in_token)
	{
		append_token(data, TOK_UNKNOWN);
		data->in_token = false;
	}
	data->start = data->end;
	if (data->input_line[data->end + 1] == '<')
	{
		data->end++;
		append_token_double(data, TOK_REDIRECT_HEREDOC);
	}
	else
		append_token(data, TOK_REDIRECT_IN);
	data->start = data->end + 1;
}

/*this functton add pipes as seperated tokens.*/
void	pipe_function(t_data *data)
{
	if (data->in_token)
	{
		append_token(data, TOK_UNKNOWN);
		data->in_token = false;
	}
	data->start = data->end;
	append_token(data, TOK_PIPE);
	data->start = data->end + 1;
}

/*this functton to handle when space is found so it will add the prevois to
new token then start the start counter for new one.*/
void	space_function(t_data *data)
{
	if (data->quote_found)
	{
		data->end++;
		return ;
	}
	if (data->in_token)
	{
		append_token(data, TOK_UNKNOWN);
		data->in_token = false;
	}
	data->start = data->end + 1;
}
