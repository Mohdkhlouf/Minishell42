/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:04:27 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/20 14:34:36 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

void	cmds_d_init(t_data *data, t_parsed_data *cmds_d)
{
	data->cmds_d = cmds_d;
	data->tokens = NULL;
	data->end = 0;
	data->start = 0;
	data->pid = NULL;
	data->in_token = false;
	data->quote_found = false;
	cmds_d->cmds = NULL;
	cmds_d->cmds_counter = 0;
	cmds_d->pipes_counter = 0;
	cmds_d->cmds_ctr = 0;
	cmds_d->red_ctr = 0;
	cmds_d->token_ctr = 0;
	data->new_delimiter = NULL;
	data->old_delim = NULL;
}

void	data_init(t_data *data, t_parsed_data *cmds_d)
{
	cmds_d_init(data, cmds_d);
	data->double_quote_found = false;
	data->first_quote_type = 0;
	data->file_seperator_found = false;
	data->variable_sign_found = false;
	data->input_line = NULL;
	data->quote_type = 0;
	data->pwd = NULL;
	data->envp = NULL;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->cline_parts = 0;
	data->tokens_conter = 0;
	data->prompt = "\001\033[1;32m\002minishell$ \001\033[0m\002";
	data->sigquit_flag = false;
	data->sigterm_flag = false;
	data->file_name = NULL;
	data->with_slash = NULL;
	data->malloc_fail_flag = false;
}

void	reading_loop(t_data *data, t_parsed_data *cmds_d)
{
	while (true)
	{
		data_init(data, cmds_d);
		heredoc_signal_rest(data);
		data->input_line = readline(data->prompt);
		if (!data->input_line)
			faild_read_line(data, cmds_d);
		else if (ft_strcmp(data->input_line, "") != 0)
		{
			if (g_signal_status == 130)
				signal_130(data);
			add_history(data->input_line);
			if (!pre_validation(data) || !lexing(data) || !tokenizing(data)
				|| !parsing(data, cmds_d) || !update_new_env(data)
				|| !execution(data, cmds_d))
			{
				command_cleanup(data, cmds_d);
				continue ;
			}
			command_cleanup(data, cmds_d);
		}
		free(data->input_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data			*data;
	t_parsed_data	*cmds_d;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	cmds_d = ft_calloc(1, sizeof(t_parsed_data));
	if (!cmds_d)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	data_init(data, cmds_d);
	if (!init_env(envp, data))
		return (free(data), free(cmds_d), 1);
	if (envp && envp[0])
		shelvl(data);
	set_prompt_signals();
	reading_loop(data, cmds_d);
	free(cmds_d);
	free(data->path);
	free(data);
	return (g_signal_status);
}
