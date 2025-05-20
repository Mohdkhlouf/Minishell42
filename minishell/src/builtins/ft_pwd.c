/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:39:51 by akumari           #+#    #+#             */
/*   Updated: 2025/05/20 14:39:52 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_pwd(t_cmds *cmd, t_data *data, int *exit_code)
{
	char	*cwd;
	int		i;

	i = 1;
	(void)data;
	*exit_code = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd failed");
		return (false);
	}
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-' && cmd->cmd[1][1] != '\0')
	{
		minishell_error("pwd", "invalid option", cmd->cmd[i]);
		minishell_error("pwd", "usage: pwd [-LP]", NULL);
		*exit_code = 1;
		free(cwd);
		return (false);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (true);
}
