/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shelvl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:59:52 by akumari           #+#    #+#             */
/*   Updated: 2025/05/21 14:01:07 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_130(t_data *data)
{
	g_signal_status = 0;
	data->exit_code = 130;
}

void	faild_read_line(t_data *data, t_parsed_data *cmds_d)
{
	ft_putstr_fd("exit\n", 1);
	free_readingloop(data, cmds_d);
	exit(0);
}

t_var	*get_env_lst(t_var *env_lst, const char *key)
{
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	shelvl(t_data *data)
{
	t_var	*env_var;
	int		shell_level;
	char	*shlvl_str;

	shell_level = 1;
	env_var = get_env_lst(data->env_lst, "SHLVL");
	if (env_var)
		shell_level = ft_atoi(env_var->value) + 1;
	shlvl_str = ft_itoa(shell_level);
	if (!shlvl_str)
	{
		free(data);
		free(data->cmds_d);
		exit(1);
	}
	update_env_list("SHLVL", shlvl_str, data);
	free(shlvl_str);
}

void	exit_shlvl(t_data *data)
{
	t_var	*env_var;
	char	*shlvl_str;
	int		shell_level;

	env_var = get_env_lst(data->env_lst, "SHLVL");
	if (env_var)
	{
		shell_level = ft_atoi(env_var->value);
		if (shell_level > 2)
		{
			shell_level--;
			shlvl_str = ft_itoa(shell_level);
			if (!shlvl_str)
			{
				free(data);
				free(data->cmds_d);
				exit(1);
			}
			update_env_list("SHLVL", shlvl_str, data);
			free(shlvl_str);
		}
	}	
}
