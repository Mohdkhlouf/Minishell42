#include "../includes/minishell.h"

void	hanlde_fd(int old, int fd)
{
	dup2(fd, old);
	close(fd);
}

void	append_handller(t_data *data, t_cmds *cmd, int *i, char *append)
{
	if (!open_output_file(data,cmd, append, O_APPEND))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

void	output_handller(t_data *data,  t_cmds *cmd, int *i, char *outfile)
{
	if (!open_output_file(data,cmd, outfile, O_TRUNC))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

void	input_handller(t_data *data, t_cmds *cmd, int *i, char *infile)
{
	if (!open_input_file(data,cmd, infile))
	{
		/*handle that needed*/
		cleanup_minishell(data);
		exit(-1);
	}
	(*i)++;
}

void	heredoc_read(t_data *data,  t_cmds *cmd, int *i, char *heredoc_filename)
{
	if (!open_input_file(data,cmd,  heredoc_filename))
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
