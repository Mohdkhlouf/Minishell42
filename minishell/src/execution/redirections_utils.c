#include "../includes/minishell.h"

bool	open_output_file(t_data *data, char *outfile, int mode)
{
	// int	fd;

	data->red_out_fd = open(outfile, O_WRONLY | O_CREAT | mode, 0644);
	if (data->red_out_fd  >= 0)
		hanlde_fd(1, data->red_out_fd );
	else
		return (perror("minishell: "), false);
	return (true);
}

bool	open_input_file(t_data *data, char *infile)
{
	// int	fd;

	// if (access(infile, F_OK) != 0)
	// 	return (print_error("No such file or directory"), false);
	// if (access(infile, R_OK) != 0)
	// 	return (print_error("Permission denied"), false);
	data->red_in_fd = open(infile, O_RDONLY);
	if (data->red_in_fd < 0)
		return (perror("minishell: "), false);
	hanlde_fd(STDIN_FILENO, data->red_in_fd);
	return (true);
}
