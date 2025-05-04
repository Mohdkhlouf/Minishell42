#include "../includes/minishell.h"

void	hanlde_fd(int old, int fd)
{
	dup2(fd, old);
	close(fd);
}

void	append_handller(t_data *data, t_cmds *cmd, int *i, char *append)
{
	(void)data;
	if (!open_output_file(cmd, append, O_APPEND))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

void	output_handller(t_data *data,  t_cmds *cmd, int *i, char *outfile)
{
	(void)data;
	if (!open_output_file(cmd, outfile, O_TRUNC))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

void	input_handller(t_data *data, t_cmds *cmd, int *i, char *infile)
{
	(void)data;
	if (!open_input_file(cmd, infile))
	{
		/*handle that needed*/
		cleanup_minishell(data);
		exit(-1);
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

bool	execute_redirections(t_data *data, t_cmds *cmd)
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
			input_handller(data,cmd, &i, cmd->reds[i + 1]);
		else if (ft_strcmp(cmd->reds[i], "<<") == 0)
			heredoc_read(data,cmd, &i, "HEREDOC_TEMP.txt");
		else if (ft_strcmp(cmd->reds[i], ">") == 0)
			output_handller(data,cmd, &i, cmd->reds[i + 1]);
		else if (ft_strcmp(cmd->reds[i], ">>") == 0)
			append_handller(data,cmd, &i, cmd->reds[i + 1]);
		i++;
	}

	return (true);
}
