#include "../includes/lexing.h"

void	quote_assign_ch(char *quote, char ch, char *temp, int *c)
{
	if (*quote == 0)
		*quote = ch;
	else if (*quote == ch)
		*quote = 0;
	else
	{
		temp[*c] = ch;
		(*c)++;
	}
}

int	assign_quotes(t_data *data, int len, int i, char *temp)
{
	int		j;
	int		c;
	char	ch;
	char	quote;

	j = 0;
	c = 0;
	quote = 0;
	while (j < len)
	{
		ch = data->tokens[i].data[j];
		if ((ch == '\'' || ch == '\"'))
			quote_assign_ch(&quote, ch, temp, &c);
		else
			temp[c++] = ch;
		j++;
	}
	temp[c] = '\0';
	if (quote != 0)
		return (-1);
	return (0);
}

void	quote_type_check(t_data *data, int i)
{
	if (data->tokens[i].data[0] == '\'')
	{
		if (!(i > 0 && data->tokens[i - 1].type
				&& data->tokens[i - 1].type != TOK_REDIRECT_HEREDOC))
		{
			data->tokens[i].type = TOK_SINGLE_QUOTE;
		}
	}
	else if (data->tokens[i].data[0] == '\"')
	{
		if (!(i > 0 && data->tokens[i - 1].type
				&& data->tokens[i - 1].type != TOK_REDIRECT_HEREDOC))
		{
			data->tokens[i].type = TOK_DOUBLE_QUOTE;
		}
	}
}

bool	quote_fixing(t_data *data, int i)
{
	char	*temp;
	int		len;
	int		result;

	len = 0;
	result = 0;
	quote_type_check(data, i);
	len = ft_strlen(data->tokens[i].data);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (false);
	result = assign_quotes(data, len, i, temp);
	if (result == -1)
	{
		print_error("quotes are not closed");
		data->exit_code = 2;
		return (free(temp), false);
	}
	free(data->tokens[i].data);
	data->tokens[i].data = ft_strdup(temp);
	if (!data->tokens[i].data)
		return (free(temp),false);
	return (free(temp), true);
}

void	redirection_setting(t_data *data, int i)
{
	if (data->tokens[i].type == TOK_UNKNOWN && i > 0)
	{
		if (data->tokens[i - 1].type == TOK_REDIRECT_IN
			&& data->tokens[i - 1].data[0] == '<')
		{
			data->tokens[i].type = TOK_REDIRECT_IN;
		}
		else if (data->tokens[i - 1].type == TOK_REDIRECT_OUT
			&& data->tokens[i - 1].data[0] == '>')
		{
			data->tokens[i].type = TOK_REDIRECT_OUT;
		}
		else if (data->tokens[i - 1].type == TOK_APPEND
			&& data->tokens[i - 1].data[0] == '>')
		{
			data->tokens[i].type = TOK_APPEND;
		}
		else if (data->tokens[i - 1].type == TOK_REDIRECT_HEREDOC
			&& data->tokens[i - 1].data[0] == '<')
		{
			data->tokens[i].type = TOK_REDIRECT_HEREDOC;
		}
	}
}
