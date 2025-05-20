/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:39:36 by akumari           #+#    #+#             */
/*   Updated: 2025/05/20 14:40:23 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_export(char **sorted_arr, t_data *data)
{
	int	i;

	i = 0;
	while (sorted_arr[i])
	{
		printf("declare -x %s", sorted_arr[i]);
		if (get_env_value(sorted_arr[i], data) && get_env_value(sorted_arr[i],
				data)[0] != '\0')
		{
			printf("=\"%s\"", get_env_value(sorted_arr[i], data));
		}
		printf("\n");
		i++;
	}
}

bool	check_valid_identifier(char *key, char *param_value)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			minishell_error("export", "not a valid identifier", param_value);
			return (false);
		}
		i++;
	}
	return (true);
}
