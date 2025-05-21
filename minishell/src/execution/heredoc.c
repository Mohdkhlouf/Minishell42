/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:12:36 by akumari           #+#    #+#             */
/*   Updated: 2025/05/21 13:15:02 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			result[j++] = delimiter[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

bool	new_delim_assign(t_data *data)
{
	if (ft_strchr(data->old_delim, '\"') || ft_strchr(data->old_delim, '\''))
	{
		data->new_delim = strip_quotes(data->old_delim);
		if (!data->new_delim)
			return (false);
	}
	else
	{
		data->new_delim = ft_strdup(data->old_delim);
		if (!data->new_delim)
			return (false);
	}
	return (true);
}

bool	here_loop(t_data *data, t_parsed_data *cmds_d, int i, int *expand)
{
	int	j;

	j = 0;
	while (true && cmds_d->cmds[i].reds[j])
	{
		if (ft_strcmp(cmds_d->cmds[i].reds[j], "<<") == 0)
		{
			if (!cmds_d->cmds[i].reds[j + 1])
				return (print_error("syntax error unexpected token"), false);
			j++;
			data->old_delim = cmds_d->cmds[i].reds[j];
			if (is_quoted_delimiter(data->old_delim) == 1)
				*expand = 0;
			if (!new_delim_assign(data))
				return (false);
			data->here_ret = handle_heredoc(data->new_delim, data, *expand);
			if (data->here_ret == -1)
				return (false);
			else if (data->here_ret == 1)
				return (set_g_signal(1), false);
			ft_free(data->new_delim);
		}
		j++;
	}
	return (true);
}

bool	exec_heredoc(t_data *data, t_parsed_data *cmds_d)
{
	int	i;
	int	expand;

	i = 0;
	expand = 1;
	while (i < data->cmds_d->cmds_counter)
	{
		if (!here_loop(data, cmds_d, i, &expand))
			return (false);
		i++;
	}
	return (true);
}
