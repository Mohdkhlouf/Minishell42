/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:20:44 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 11:33:22 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hanlde_fd(int old, int fd)
{
	dup2(fd, old);
	if (fd != -1)
		ft_close(&fd);
}

bool	open_output_file(t_cmds *cmd, char *outfile, int mode)
{
	cmd->red_out_fd = open(outfile, O_WRONLY | O_CREAT | mode, 0644);
	if (cmd->red_out_fd >= 0)
		hanlde_fd(STDOUT_FILENO, cmd->red_out_fd);
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
	{
		if (cmd->red_in_fd != -1)
		{
			dup2(cmd->red_in_fd, STDIN_FILENO); // Redirect STDIN to red_in_fd
			close(cmd->red_in_fd);              // Close the original fd
			cmd->red_in_fd = -1;                // Mark it as closed
		}
	}
	return (true);
}

// bool	open_input_file(t_cmds *cmd, char *infile)
// {
// 	cmd->red_in_fd = open(infile, O_RDONLY);
// 	if (cmd->red_in_fd < 0)
// 		return (print_error_2msgs(infile, strerror(errno)), false);
// 	else
// 		hanlde_fd(STDIN_FILENO, cmd->red_in_fd);
// 	return (true);
// }

bool	allocate_pid(t_data *data, t_parsed_data *cmds_d)
{
	data->pid = ft_calloc(cmds_d->cmds_counter, sizeof(pid_t));
	if (!data->pid)
	{
		return (false);
	}
	return (true);
}
