/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:05:06 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 13:07:53 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_list(t_var *env)
{
	t_var	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	free_matrix(char **env)
{
	int	i;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	if (env)
		free(env);
	env = NULL;
	return (0);
}

int	free_2arr_general(char **arr)
{
	int	i;

	if (!arr)
		return (1);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (0);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens && i < data->tokens_conter)
	{
		if (data->tokens[i].data)
		{
			free(data->tokens[i].data);
			data->tokens[i].data = NULL;
		}
		i++;
	}
	free(data->tokens);
	data->tokens = NULL;
	free(data->pid);
	if (data->pipe_fd[0] != -1)
		ft_close(&data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		ft_close(&data->pipe_fd[1]);
}
