#include "../includes/minishell.h"

bool	open_output_file(t_data *data,t_cmds *cmd, char *outfile, int mode)
{
	// int	fd;

	cmd->red_out_fd = open(outfile, O_WRONLY | O_CREAT | mode, 0644);
	if (cmd->red_out_fd  >= 0)
		hanlde_fd(STDOUT_FILENO, cmd->red_out_fd );
	else
		return (perror("minishell: "), false);
	return (true);
}

bool	open_input_file(t_data *data,t_cmds *cmd, char *infile)
{
	// int	fd;

	// if (access(infile, F_OK) != 0)
	// 	return (print_error("No such file or directory"), false);
	// if (access(infile, R_OK) != 0)
	// 	return (print_error("Permission denied"), false);
	cmd->red_in_fd = open(infile, O_RDONLY);
	if (cmd->red_in_fd < 0)
		return (perror("minishell: "), false);
	else 
		hanlde_fd(STDIN_FILENO, cmd->red_in_fd);
	return (true);
}
