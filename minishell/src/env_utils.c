/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:52:27 by akumari           #+#    #+#             */
/*   Updated: 2025/05/21 14:02:41 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env_list(char *key, char *value, t_data *data)
{
	t_var	*env;

	if (!key)
		return ;
	env = data->env_lst;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			if (value)
			{
				env->value = ft_strdup(value);
				if (!env->value)
					env->value = NULL;
			}
			else
				env->value = NULL;
			return ;
		}
		env = env->next;
	}
}

void	add_new_env_variable(char *key, char *value, t_data *data)
{
	t_var	*new_node;

	if (!key || !data)
		return ;
	new_node = malloc(sizeof(t_var));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (free(new_node), (void)0);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (free(new_node->key), free(new_node), (void)0);
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	env_addtolist(&data->env_lst, new_node);
}

int	get_env_len(t_var *env)
{
	int	count;

	count = 0;
	if (!env)
		return (-1);
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*get_env_key(char *key, t_data *data)
{
	t_var	*env;

	env = data->env_lst;
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0
			&& (ft_strlen(env->key) == ft_strlen(key)))
			return (env->key);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(char *key, t_data *data)
{
	t_var	*env;

	env = data->env_lst;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0
			&& (ft_strlen(env->key) == ft_strlen(key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
