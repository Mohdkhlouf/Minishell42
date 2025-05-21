/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:05:06 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 13:17:56 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_minishell(t_data *data)
{
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	free_matrix(data->envp);
	free_2arr_general(data->parsed_path);
	free_2arr_general(data->words);
	ft_free(data->pwd);
	ft_free(data->input_line);
	free_env_list(data->env_lst);
	free_cmds_d(data->cmds_d);
	free_data(data);
	free(data->cmds_d);
}
