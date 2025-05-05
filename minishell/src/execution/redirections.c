#include "../includes/minishell.h"

void	hanlde_fd(int old, int fd)
{
	dup2(fd, old);
	close(fd);
}

void	append_handller(t_data *data, t_cmds *cmd, int *i, char *append, int *exit_code)
{
	(void)data;
	if (!open_output_file(cmd, append, O_APPEND))
	{
		*exit_code = 1;
		/*handle that needed*/
		exit(*exit_code);
	}
	(*i)++;
}

void	output_handller(t_data *data,  t_cmds *cmd, int *i, char *outfile, int *exit_code)
{
	(void)data;
	if (!open_output_file(cmd, outfile, O_TRUNC))
	{
		*exit_code = 1;
		/*handle that needed*/
		exit(*exit_code);
	}
	(*i)++;
}

void	input_handller(t_data *data, t_cmds *cmd, int *i, char *infile, int *exit_code)
{
	(void)data;

	if (!open_input_file(cmd, infile))
	{
		/*handle that needed*/
		*exit_code = 1;
		cleanup_minishell(data);
		exit(*exit_code);
	}
	(*i)++;
}

void	heredoc_read(t_data *data,  t_cmds *cmd, int *i, char *heredoc_filename)
{
	(void)data;
	if (!open_input_file(cmd,  heredoc_filename))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

bool	execute_redirections(t_data *data, t_cmds *cmd, int *exit_code)
{
	int	i;

	i = 0;
	if (!cmd->reds) // protect against NULL cmds_d or reds
		return (__FLT128_HAS_DENORM__);
	while (cmd->reds[i])
	{
		if (cmd->reds[i] == NULL)
			break ;
		if (ft_strcmp(cmd->reds[i], "<") == 0)
			input_handller(data,cmd, &i, cmd->reds[i + 1], exit_code);
		else if (ft_strcmp(cmd->reds[i], "<<") == 0)
			heredoc_read(data,cmd, &i, "HEREDOC_TEMP.txt");
		else if (ft_strcmp(cmd->reds[i], ">") == 0)
			output_handller(data,cmd, &i, cmd->reds[i + 1], exit_code);
		else if (ft_strcmp(cmd->reds[i], ">>") == 0)
			append_handller(data,cmd, &i, cmd->reds[i + 1], exit_code);
		i++;
	}

	return (true);
}
