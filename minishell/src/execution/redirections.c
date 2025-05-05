#include "../includes/minishell.h"

void	hanlde_fd(int old, int fd)
{
	dup2(fd, old);
	close(fd);
}

bool	append_handller(t_data *data, t_cmds *cmd, int *i, char *append, int *exit_code)
{
	(void)data;
	if (!open_output_file(cmd, append, O_APPEND))
	{
		*exit_code = 1;
		return (false);
	}
	(*i)++;
	return (true);
}

bool	output_handller(t_data *data,  t_cmds *cmd, int *i, char *outfile, int *exit_code)
{
	(void)data;
	if (!open_output_file(cmd, outfile, O_TRUNC))
	{
		*exit_code = 1;
		return (false);
	}
	(*i)++;
	return (true);
}

bool	input_handller(t_data *data, t_cmds *cmd, int *i, char *infile, int *exit_code)
{
	(void)data;

	if (!open_input_file(cmd, infile))
	{
		*exit_code = 1;
		return (false);
	}
	(*i)++;
	return (true);
}

bool	heredoc_read(t_data *data,  t_cmds *cmd, int *i, char *heredoc_filename)
{
	(void)data;
	if (!open_input_file(cmd,  heredoc_filename))
	{
		return (false);
	}
	(*i)++;
	return (true);
}

bool	execute_redirections(t_data *data, t_cmds *cmd, int *exit_code)
{
	int	i;
	bool result;

	result = true;
	i = 0;
	if (!cmd->reds) // protect against NULL cmds_d or reds
		return (false);
	while (cmd->reds[i] && result)
	{
		if (cmd->reds[i] == NULL)
			break ;
		if (ft_strcmp(cmd->reds[i], "<") == 0)
			result = input_handller(data,cmd, &i, cmd->reds[i + 1], exit_code);
		else if (ft_strcmp(cmd->reds[i], "<<") == 0)
			result = heredoc_read(data,cmd, &i, "HEREDOC_TEMP.txt");
		else if (ft_strcmp(cmd->reds[i], ">") == 0)
			result = output_handller(data,cmd, &i, cmd->reds[i + 1], exit_code);
		else if (ft_strcmp(cmd->reds[i], ">>") == 0)
			result = append_handller(data,cmd, &i, cmd->reds[i + 1], exit_code);
		i++;
	}
	return (result);
}

