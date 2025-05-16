
#include "../includes/lexing.h"

// void	assign_quotes(t_data *data, int len, int i, char *temp)
// {
// 	int	c;
// 	int	j;

// 	c = 0;
// 	j = 0;
// 	while (j < len)
// 	{
// 		if (data->tokens[i].data[j] == '\'' && data->quote_type == 0)
// 			data->quote_type = '\'';
// 		if (data->tokens[i].data[j] == '\"' && data->quote_type == 0)
// 			data->quote_type = '\"';
// 		if (data->tokens[i].data[j] == data->quote_type
// 			|| (data->tokens[i].data[j] == '\'' && data->quote_type == 0)
// 				|| (data->tokens[i].data[j] == '\"' && data->quote_type == 0))
// 			j++;
// 		else
// 		{
// 			temp[c] = data->tokens[i].data[j];
// 			c++;
// 			j++;
// 		}
// 	}
// 	data->quote_type = 0;
// 	temp[c] = '\0';
// }

int	assign_quotes(t_data *data, int len, int i, char *temp)
{
	int		j;
	int		c;
	char	ch;

	j = 0;
	c = 0;
	char quote = 0; // No active quote initially
	while (j < len)
	{
		ch = data->tokens[i].data[j];
		if ((ch == '\'' || ch == '\"'))
		{
			if (quote == 0)
			{
				// Starting a quote context
				quote = ch;
				j++;
			}
			else if (quote == ch)
			{
				// Closing the same quote
				quote = 0;
				j++;
			}
			else
			{
				// Inside a quote, different quote type → literal char
				temp[c++] = ch;
				j++;
			}
		}
		else
		{
			// Normal character
			temp[c++] = ch;
			j++;
		}
	}
	temp[c] = '\0';
	if (quote != 0)
	{
		// Unclosed quote context
		return (-1);
	}
	return (0);
}

bool	quote_fixing(t_data *data, int i)
{
	char	*temp;
	int		len;
	int		result;

	if (data->tokens[i].data[0] == '\'')
	{
		if (!(i > 0 && data->tokens[i - 1].type && data->tokens[i
				- 1].type != TOK_REDIRECT_HEREDOC))
			data->tokens[i].type = TOK_SINGLE_QUOTE;
	}
	else if (data->tokens[i].data[0] == '\"')
	{
		if (!(i > 0 && data->tokens[i - 1].type && data->tokens[i
				- 1].type != TOK_REDIRECT_HEREDOC))
			data->tokens[i].type = TOK_DOUBLE_QUOTE;
	}
	len = ft_strlen(data->tokens[i].data);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (false);
	// assign_quotes(data, len, i, temp);
	result = assign_quotes(data, len, i, temp);
	if (result == -1)
	{
		print_error("quotes are not closed");
		data->exit_code = 2;
		free(temp);
		return (false);
	}
	free(data->tokens[i].data);
	data->tokens[i].data = ft_strdup(temp);
	free(temp);
	return (true);
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
