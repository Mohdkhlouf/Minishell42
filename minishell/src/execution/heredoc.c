#include "../includes/minishell.h"

int	is_quoted_delimiter(char *delimiter)
{
	int		count;
	size_t	i;
	size_t	len;

	count = 0;
	i = 0;
	if (!delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (len < 2)
		return (0);
	while (delimiter[i])
	{
		if ((delimiter[i] == '\'' || delimiter[i] == '"'))
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	else
		return (0);
}

char	*strip_quotes(char *delimiter)
{
	size_t	i;
	size_t	j;
	char	*result;
	size_t	len;

	i = 0;
	j = 0;
	if (!delimiter)
		return (NULL);
	len = ft_strlen(delimiter);
	result = malloc(sizeof(len) + 1);
	if (!result)
		return (NULL);
	while (delimiter[i])
	{
		if ((delimiter[i] != '\'' && delimiter[i] != '"'))
			result[j++] = delimiter[i]; // segfault
		i++;
	}
	result[j] = '\0';
	return (result);
}
void	set_g_signal(int value)
{
	g_signal_status = value;
}

bool	new_delim_assign(t_data *data)
{
	if (ft_strchr(data->old_delim, '\"') || ft_strchr(data->old_delim, '\''))
		{
			data->new_delimiter = strip_quotes(data->old_delim);
			if (!data->new_delimiter)
				return (false);
		}
	else
	{
		data->new_delimiter = ft_strdup(data->old_delim);
		if (!data->new_delimiter)
				return (false);
	}
	return (true);
}
bool	exec_heredoc(t_data *data, t_parsed_data *cmds_d)
{
	int	i;
	int	j;
	int	expand;
	int	test;

	test = 0;
	i = 0;
	j = 0;
	expand = 1;
	while (i < data->cmds_d->cmds_counter)
	{
		j = 0;
		while (true && cmds_d->cmds[i].reds[j])
		{
			// if (!cmds_d->cmds[i].reds[j])
			// 	break ;
			if (ft_strcmp(cmds_d->cmds[i].reds[j], "<<") == 0)
			{
				if (!cmds_d->cmds[i].reds[j + 1])
				{
					printf("syntax error: expected delimiter after <<\n");
					break ;
				}
				j++;
				data->old_delim = cmds_d->cmds[i].reds[j];
				if (is_quoted_delimiter(data->old_delim) == 1)
					expand = 0;
				if (!new_delim_assign(data))
					return (false);
				test = handle_heredoc(data->new_delimiter, data, expand);
				if (test == -1)
					return (false);
				else if (test == 1)
					return (set_g_signal(1), false);
				ft_free(data->new_delimiter);
			}
			j++;
		}
		i++;
	}
	return (true);
}
