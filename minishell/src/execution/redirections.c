#include "../includes/minishell.h"

void	hanlde_fd(int old, int fd)
{
	dup2(fd, old);
	close(fd);
}

void	append_handller(t_data *data, int *i, char *append)
{
	if (!open_output_file(append, O_APPEND))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

void	output_handller(t_data *data, int *i, char *outfile)
{
	if (!open_output_file(outfile, O_TRUNC))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

void	input_handller(t_data *data, int *i, char *infile)
{
	if (!open_input_file(infile))
	{
		/*handle that needed*/
		cleanup_minishell(data);
		exit(-1);
	}
	(*i)++;
}

void	heredoc_read(t_data *data, int *i, char *heredoc_filename)
{
	if (!open_input_file(heredoc_filename))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

bool	execute_redirections(t_data *data, t_cmds *cmds_d)
{
	int	i;

	i = 0;
	if (!cmds_d->reds) // protect against NULL cmds_d or reds
		return (__FLT128_HAS_DENORM__);
	while (cmds_d->reds[i])
	{
		if (cmds_d->reds[i] == NULL)
			break ;
		if (ft_strcmp(cmds_d->reds[i], "<") == 0)
			input_handller(data, &i, cmds_d->reds[i + 1]);
		else if (ft_strcmp(cmds_d->reds[i], "<<") == 0)
			heredoc_read(data, &i, "HEREDOC_TEMP.txt");
		else if (ft_strcmp(cmds_d->reds[i], ">") == 0)
			output_handller(data, &i, cmds_d->reds[i + 1]);
		else if (ft_strcmp(cmds_d->reds[i], ">>") == 0)
			append_handller(data, &i, cmds_d->reds[i + 1]);
		i++;
	}

	return (true);
}
