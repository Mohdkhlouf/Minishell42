#include "../includes/lexing.h"

bool	pre_validation(t_data *data)
{
	int	len;

	len = 0;
	len = ft_strlen(data->input_line);
	if ((len == 2) && (ft_strcmp(data->input_line, "\"\"") == 0
			|| ft_strcmp(data->input_line, "''") == 0))
	{
		data->exit_code = 127;
		return (print_error("Command '' not found"), false);
	}
	if (data->input_line[len - 1] == '<' || data->input_line[len - 1] == '>'
		|| data->input_line[len - 1] == '|')
	{
		data->exit_code = 2;
		return (print_error("syntax error near unexpected token `|'"), false);
	}
	if (len == 1 && data->input_line[len - 1] == '.')
	{
		data->exit_code = 2;
		return (print_error_2msgs(".", "filename argument required"), false);
	}
	return (true);
}

void	set_ecode_print_pipe(t_data *data, int value)
{
	print_error("syntax error near unexpected token `|'");
	data->exit_code = value;
}

void	set_ecode_print(t_data *data, int value, char *msg)
{
	print_error(msg);
	data->exit_code = value;
}

bool	quotes_validation(t_data *data)
{
	if (data->quote_found && data->first_quote_type == 1)
		return (set_ecode_print(data, 2, "quotes are not closed"), false);
	if (data->double_quote_found && data->first_quote_type == 2)
		return (set_ecode_print(data, 2, "quotes are not closed"), false);
	return (true);
}

bool	validation(t_data *data)
{
	int	i;

	i = 0;
	if (data->tokens_conter == 1)
		return (true);
	while (data->tokens[i].data && i < data->tokens_conter)
	{
		if (data->tokens[0].type == 3)
			return (set_ecode_print_pipe(data, 2), false);
		if (data->tokens[i].type == 3 && data->tokens[i + 1].type == 3)
			return (set_ecode_print_pipe(data, 2), false);
		if ((data->tokens[i].type == TOK_REDIRECT_IN
				|| data->tokens[i].type == TOK_REDIRECT_OUT
				|| data->tokens[i].type == TOK_REDIRECT_HEREDOC
				|| data->tokens[i].type == TOK_APPEND) && data->tokens[i
			+ 1].type == 3)
		{
			return (set_ecode_print_pipe(data, 2), false);
		}
		i++;
	}
	if (!quotes_validation(data))
		return (false);
	return (true);
}
