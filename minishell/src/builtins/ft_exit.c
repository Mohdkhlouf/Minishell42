/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:39:24 by akumari           #+#    #+#             */
/*   Updated: 2025/05/20 14:39:25 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_exit_code(char *arg, int *exit_code)
{
	long long	arg_value;

	if (!ft_is_numeric(arg))
	{
		minishell_error("exit", "numeric argument required", arg);
		*exit_code = 2;
		return (1);
	}
	arg_value = ft_atoi(arg);
	if (arg_value == LONG_MAX || arg_value == LONG_MIN)
	{
		minishell_error("exit", "numeric argument required", arg);
		*exit_code = 2;
		return (1);
	}
	*exit_code = (int)arg_value;
	return (0);
}

bool	ft_exit(t_cmds *cmd, t_data *data, int *exit_code)
{
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		*exit_code = 1;
		print_error("exit: too many arguments");
		return (false);
	}
	printf("exit\n");
	exit_shlvl(data);
	if (cmd->cmd[1])
		parse_exit_code(cmd->cmd[1], exit_code);
	if (cmd->saved_stdin > 0)
		close(cmd->saved_stdin);
	if (cmd->saved_stdout > 0)
		close(cmd->saved_stdout);
	cleanup_minishell(data);
	free(data);
	exit(*exit_code);
}
