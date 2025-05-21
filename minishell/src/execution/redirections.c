/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:20:12 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 12:57:31 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	append_handller(t_cmds *cmd, int *i, char *append, int *exit_code)
{
	if (!append)
		return (print_error("ambiguous redirect"), false);
	if (!open_output_file(cmd, append, O_APPEND))
	{
		*exit_code = 1;
		return (false);
	}
	(*i)++;
	return (true);
}

bool	output_handller(t_cmds *cmd, int *i, char *outfile, int *exit_code)
{
	if (!outfile)
		return (print_error("ambiguous redirect"), false);
	if (!open_output_file(cmd, outfile, O_TRUNC))
	{
		*exit_code = 1;
		return (false);
	}
	(*i)++;
	return (true);
}

bool	input_handller(t_cmds *cmd, int *i, char *infile, int *exit_code)
{
	if (!infile)
		return (print_error("ambiguous redirect"), false);
	if (!open_input_file(cmd, infile))
	{
		*exit_code = 1;
		return (false);
	}
	(*i)++;
	return (true);
}

bool	heredoc_read(t_cmds *cmd, int *i, char *heredoc_filename)
{
	if (!open_input_file(cmd, heredoc_filename))
	{
		return (false);
	}
	(*i)++;
	return (true);
}

bool	execute_redirections(t_data *data, t_cmds *cmd, int *exit_code)
{
	int		i;
	bool	result;

	result = true;
	i = 0;
	if (!cmd->reds)
		return (false);
	while (cmd->reds[i] && result)
	{
		if (cmd->reds[i] == NULL)
			break ;
		if (ft_strcmp(cmd->reds[i], "<") == 0)
			result = input_handller(cmd, &i, cmd->reds[i + 1], exit_code);
		else if (ft_strcmp(cmd->reds[i], "<<") == 0)
			result = heredoc_read(cmd, &i, "HEREDOC_TEMP.txt");
		else if (ft_strcmp(cmd->reds[i], ">") == 0)
			result = output_handller(cmd, &i, cmd->reds[i + 1], exit_code);
		else if (ft_strcmp(cmd->reds[i], ">>") == 0)
			result = append_handller(cmd, &i, cmd->reds[i + 1], exit_code);
		i++;
	}
	return (result);
}
