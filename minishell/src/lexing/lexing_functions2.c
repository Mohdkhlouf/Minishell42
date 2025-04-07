#include "../includes/lexing.h"

/* this function to continue when the input is nprmal not from the needed
charaters*/

void	normal_function(t_data *data)
{
	data->in_token = true;
	if (data->input_line[data->end] == '\''
		|| data->input_line[data->end] == '\"')
	{
		if (data->quote_found == true)
			data->quote_found = false;
		else if (data->quote_found == false)
			data->quote_found = true;
	}
}
/* this funcction to add variable tokens like $HOME*/

void	env_variable_function(t_data *data)
{
	if (data->in_token)
	{
		append_token(data, TOK_ENV_VAR);
		data->in_token = false;
	}
	data->start = data->end;
}
/* this funcction to add the end of line null terminator as a seperate token*/
void	eof_function(t_data *data)
{
	if (data->double_quote_found || data->quote_found)
	{
		printf("quotes are not closed");
		exit(FAILIURE);
	}
	if (data->in_token)
	{
		append_token(data, TOK_UNKNOWN);
		data->in_token = false;
	}
	data->start = data->end;
	append_token(data, TOK_EOF);
	data->start = data->end + 1;
}
