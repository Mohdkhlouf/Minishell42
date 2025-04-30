#include "../includes/minishell.h"




bool	open_output_file(char *outfile, int mode)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | mode, 0644);
	if (fd >= 0)
		hanlde_fd(1, fd);
	else
		return (perror("minishell: "), false);
	return (true);
}

bool	open_input_file(char *infile)
{
	int	fd;

	// if (access(infile, F_OK) != 0)
	// 	return (print_error("No such file or directory"), false);
	// if (access(infile, R_OK) != 0)
	// 	return (print_error("Permission denied"), false);
	fd = open(infile, O_RDONLY);
	if (fd < 0)
		return (perror("minishell: "), false);
	hanlde_fd(STDIN_FILENO, fd);
	return (true);
}
