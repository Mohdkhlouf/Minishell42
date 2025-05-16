#include "../includes/minishell.h"

int is_quoted_delimiter(char *delimiter)
{
	int count = 0;
	size_t i = 0;
	if (!delimiter)
		return (0);
	size_t len = ft_strlen(delimiter);
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

char *strip_quotes(char *delimiter)
{
	size_t i = 0;
	size_t j = 0;
	char *result;

	if (!delimiter)
		return (NULL);
	size_t len = ft_strlen(delimiter);
	// if (len < 2)
	// 	return ft_strdup(delimiter);
	result = malloc(sizeof(len) + 1); // malloc check
	while (delimiter[i])
	{
		if ((delimiter[i] != '\'' && delimiter[i] != '"'))
			result[j++] = delimiter[i]; // segfault
		i++;
	}
	result[j] = '\0';
	return (result);
}
void set_g_signal(int value)
{
	g_signal_status = value;
}

bool exec_heredoc(t_data *data, t_parsed_data *cmds_d)
{
	int i;
	int j;
	int expand;
	char *new_delimiter;
	char *old_delim;
	int test;

	test = 0;
	i = 0;
	j = 0;
	expand = 1;
	new_delimiter = NULL;
	old_delim = NULL;
	while (i < data->cmds_d->cmds_counter)
	{
		j = 0;
		while (true && cmds_d->cmds[i].reds[j])
		{
			char *cmd_exist = cmds_d->cmds[i].reds[j];
			if (!cmd_exist)
				break;

			if (ft_strcmp(cmds_d->cmds[i].reds[j], "<<") == 0)
			{
				if (!cmds_d->cmds[i].reds[j + 1])
				{
					printf("syntax error: expected delimiter after <<\n");
					break;
				}
				j++;
				old_delim = cmds_d->cmds[i].reds[j];
				if (is_quoted_delimiter(old_delim) == 1)
					expand = 0;
				if (ft_strchr(old_delim,'\"') || ft_strchr(old_delim,'\''))
					new_delimiter = strip_quotes(old_delim);
				else
					new_delimiter = ft_strdup(old_delim);
				test = handle_heredoc(new_delimiter, data, expand);
				if (test == -1)
					return (false);
				else if (test == 1)		
					return (set_g_signal(1), false);
				ft_free(new_delimiter);
			}
			j++;
		}
		i++;
	}
	return (true);
}
