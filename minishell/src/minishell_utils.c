/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:20:09 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/04 12:06:18 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_data(t_data * data)
{
    int i;

    i = 0;
    while(data->tokens && i < data->tokens_conter)
    {
        if (data->tokens[i].data)
            free(data->tokens[i].data);
        i++;
    }
    free(data->tokens);
    free(data->input_line);

}

void print_error(char *msg)
{
    dup2(STDERR_FILENO, STDOUT_FILENO);
    printf("minishell:%s", msg);
}

void print_error_exit(char *msg, t_data *data, t_vars_data *var)
{
    if (msg)
        print_error(msg);
    if(data)
        free_data(data);
    if(var)
        free_var(var);
}

// int ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t i;

// 	i = 0;
// 	while ((s1[i] || s2[i]))
// 	{
// 		if ((unsigned char)s1[i] != (unsigned char)s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

char *get_path(char **env)
{
	char *path;
	int i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			path = ft_strdup(env[i] + 4);
			if (path == NULL)
				return (NULL);
			break;
		}
		i++;
	}
	return (path);
}


void free_env_list(t_var *node)
{
	t_var *tmp;
	while (node)
	{
		tmp = node;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		node = node->next;
	}
}

int free_matrix(char **env)
{
	int i;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}