
#include "../includes/lexing.h"


void	assign_quotes(t_data *data, int len, int i, char *temp)
{
	int	c;
	int	j;

	c = 0;
	j = 0;
	while (j < len)
	{
		if (data->tokens[i].data[j] == '\'' && data->quote_type == 0)
			data->quote_type = '\'';
		if (data->tokens[i].data[j] == '\"' && data->quote_type == 0)
			data->quote_type = '\"';
		if (data->tokens[i].data[j] == data->quote_type
			|| (data->tokens[i].data[j] == '\'' && data->quote_type == 0)
				|| (data->tokens[i].data[j] == '\"' && data->quote_type == 0))
			j++;
		else
		{
			temp[c] = data->tokens[i].data[j];
			c++;
			j++;
		}
	}
	data->quote_type = 0;
	temp[c] = '\0';
}

void	quote_fixing(t_data *data, int i)
{
	char	*temp;
	int		len;

	if (data->tokens[i].data[0] == '\'' && data->tokens[i - 1].type != TOK_REDIRECT_HEREDOC )
		data->tokens[i].type = TOK_SINGLE_QUOTE;
	else if (data->tokens[i].data[0] == '\"' && data->tokens[i - 1].type != TOK_REDIRECT_HEREDOC)
		data->tokens[i].type = TOK_DOUBLE_QUOTE;
	len = ft_strlen(data->tokens[i].data);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		exit(EXIT_FAILURE);
	assign_quotes(data, len, i, temp);
	free(data->tokens[i].data);
	data->tokens[i].data = ft_strdup(temp);
	free(temp);
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
