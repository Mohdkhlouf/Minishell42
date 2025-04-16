#include "../includes/minishell.h"


void hanlde_fd(int old, int fd)
{
	dup2(fd, old);
	close(fd);
}

bool	open_output_file(char *outfile, int mode)
{
	int	fd;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) != 0)
			return (print_error(strerror(errno)), false);

	fd = open(outfile, O_WRONLY | O_CREAT | mode, 0644);
	if (fd >= 0)
		hanlde_fd(1 , fd);
	else
		return (print_error(strerror(errno)), false);

	return (true);
}


bool	open_input_file(char *infile)
{
	int	fd;

	if (access(infile, F_OK) == 0)
	{
		if (access(infile, R_OK) == 0)
		{
			fd = open(infile, O_RDONLY);
			if (fd >= 0)
				hanlde_fd(0, fd);
			else
				return (print_error(strerror(errno)), false);
		}
			
		else
			return (print_error(strerror(errno)), false);
	}
	else
		return (print_error(strerror(errno)), false);
	return (true);
}
void	heredoc_handller(int *i, char *heredoc)
{
	printf("heredoc is %s:", heredoc);
	// if (!open_input_file(infile))
	// {
	// 	/*handle that needed*/
	// 	exit(-1);
	// }
	(*i)++;
}
void	append_handller(int *i, char *append)
{
	if (!open_output_file(append, O_APPEND))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

void	output_handller(int *i, char *outfile)
{
	if (!open_output_file(outfile, O_TRUNC))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}

void	input_handller(int *i, char *infile)
{
	if (!open_input_file(infile))
	{
		/*handle that needed*/
		exit(-1);
	}
	(*i)++;
}
void	execute_redirections(t_data *data, t_cmds *cmds_d)
{
	(void) data;
	int i;

	i = 0;
	while (cmds_d->reds[i])
	{
		if (ft_strcmp(cmds_d->reds[i], "<") == 0)
			input_handller(&i, cmds_d->reds[i + 1]);
		else if (ft_strcmp(cmds_d->reds[i], "<<") == 0)
			heredoc_handller(&i, cmds_d->reds[i + 1]);
		else if (ft_strcmp(cmds_d->reds[i], ">") == 0)
			output_handller(&i, cmds_d->reds[i + 1]);
		else if (ft_strcmp(cmds_d->reds[i], ">>") == 0)
			append_handller(&i, cmds_d->reds[i + 1]);
		i++;
	}
}
