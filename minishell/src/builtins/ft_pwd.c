/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:41:46 by akumari           #+#    #+#             */
/*   Updated: 2025/04/04 15:20:15 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_data *data)
{
	if (data->words[0] && data->words[1])
	{
		printf("\033[0;31mpwd: too many arguments\033[0m\n");
		return (1);
	}
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		perror("getcwd failed");
		return (1);
	}
	printf("\033[0;32m%s\033[0m\n", data->pwd);
	free(data->pwd);
	return (0);
}
