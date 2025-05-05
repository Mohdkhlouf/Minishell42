#include "../includes/minishell.h"

bool	open_output_file(t_cmds *cmd, char *outfile, int mode)
{
	cmd->red_out_fd = open(outfile, O_WRONLY | O_CREAT | mode, 0644);
	if (cmd->red_out_fd  >= 0)
		hanlde_fd(STDOUT_FILENO, cmd->red_out_fd );
	else
		return (print_error_2msgs(outfile, strerror(errno)), false);
	return (true);
}

bool	open_input_file(t_cmds *cmd, char *infile)
{
	cmd->red_in_fd = open(infile, O_RDONLY);
	if (cmd->red_in_fd < 0)
		return (print_error_2msgs(infile, strerror(errno)), false);
	else 
		hanlde_fd(STDIN_FILENO, cmd->red_in_fd);
	return (true);
}
