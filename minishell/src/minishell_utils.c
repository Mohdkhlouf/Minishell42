/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:20:09 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/03/28 14:20:58 by mkhlouf          ###   ########.fr       */
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