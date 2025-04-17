#include "../includes/minishell.h"

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

bool	open_output_file(char *outfile, int mode)
{
	int	fd;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) != 0)
		return (print_error(strerror(errno)), false);
	fd = open(outfile, O_WRONLY | O_CREAT | mode, 0644);
	if (fd >= 0)
		hanlde_fd(1, fd);
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
