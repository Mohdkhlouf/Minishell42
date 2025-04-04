/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:02:18 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/03 17:33:23 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (data->tokens[i].data[0] == '\'')
		data->tokens[i].type = TOK_SINGLE_QUOTE;
	else if (data->tokens[i].data[0] == '\"')
		data->tokens[i].type = TOK_DOUBLE_QUOTE;
	len = ft_strlen(data->tokens[i].data);
	temp = malloc(sizeof(char) * len + 1);
	if (!temp)
		exit(EXIT_FAILURE);
	assign_quotes(data, len, i, temp);
	free(data->tokens[i].data);
	data->tokens[i].data = ft_strdup(temp);
	free(temp);
}

void	var_handler(t_data *data, int i)
{
	char	*path;
	char	*var;
	char	*temp;
	int		len;
	int		j;

	j = 0;
	temp = NULL;
	var = NULL;
	path = NULL;
	len = ft_strlen(data->tokens[i].data);
	search_for_file_seperator(data, i, len, &j);
	if (data->file_seperator_found)
	{
		var = ft_substr(data->tokens[i].data, 0, j);
		temp = ft_substr(data->tokens[i].data, j, len);
	}
	else
		var = data->tokens[i].data;
	if (getenv(var + 1))
		path = ft_strdup(getenv(var + 1));
	else
		path = ft_strdup("");
	path_set_and_join(data, i, temp, path);
	free(var);
	free(temp);
	free(path);
}

void	redirection_setting(t_data *data, int i)
{
	if (data->tokens[i].type == TOK_UNKNOWN && i > 0)
	{
		if (data->tokens[i - 1].type == TOK_REDIRECT_IN && data->tokens[i - 1].data[0] == '<')
			data->tokens[i].type = TOK_REDIRECT_IN;
		else if (data->tokens[i - 1].type == TOK_REDIRECT_OUT && data->tokens[i - 1].data[0] == '>')
			data->tokens[i].type = TOK_REDIRECT_OUT;
		else if (data->tokens[i - 1].type == TOK_APPEND && data->tokens[i - 1].data[0] == '>')
			data->tokens[i].type = TOK_APPEND;
		else if (data->tokens[i - 1].type == TOK_REDIRECT_HEREDOC && data->tokens[i - 1].data[0] == '<')
			data->tokens[i].type = TOK_REDIRECT_HEREDOC;
	}
}

int	tokenizing(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tokens_conter)
	{
		if (data->tokens[i].data[0] == '$')
			var_handler(data, i);
		else if ((data->tokens[i].data[0] == '\"')
			&& ft_strchr(data->tokens[i].data, '$'))
			var_handler2(data, i);
		if (ft_strchr(data->tokens[i].data, '\'')
				|| ft_strchr(data->tokens[i].data, '\"'))
		{
			quote_fixing(data, i);
		}
		redirection_setting(data, i);
		i++;
	}
	print_tokens(data);
	return (SUCCESS);
}
