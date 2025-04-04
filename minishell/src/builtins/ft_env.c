/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:41:24 by akumari           #+#    #+#             */
/*   Updated: 2025/04/04 15:38:05 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_data *data)
{
	t_var	*env;

	env = data->env_lst;
	if (data->words[0] && data->words[1])
	{
		printf("\033[0;31menv: more than one arguments are not supported\033[0m\n");
		return (1);
	}
	while (env)
	{
		printf("\033[0;32m%s=%s\033[0m\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
