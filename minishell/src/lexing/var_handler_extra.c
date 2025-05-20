/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:58:27 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/20 13:58:29 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexing.h"

void	case_allnum(char *token, t_vars_data *var, char *temp)
{
	var->var_is_found = false;
	temp = ft_substr(token, var->start, var->c - var->start);
	if (!temp)
	{
		var->var_malloc_flag = true;
		return ;
	}
	if (!process_add(var, temp))
		return ;
	var->start = var->c;
}

void	case_shell_index(char *token, t_vars_data *var, char *temp)
{
	var->var_is_found = false;
	temp = ft_substr(token, var->start, 2);
	if (!temp)
	{
		var->var_malloc_flag = true;
		return ;
	}
	if (!process_add(var, temp))
		return ;
	var->start = var->c + 1;
}

void	case_exit_code(char *token, t_vars_data *var, char *temp)
{
	var->var_is_found = false;
	temp = ft_substr(token, var->start, 2);
	if (!temp)
	{
		var->var_malloc_flag = true;
		return ;
	}
	if (!process_add(var, temp))
		return ;
	var->start = var->c + 1;
}

void	case_normal(char *token, t_vars_data *var, char *temp)
{
	var->var_is_found = true;
	if (var->c != 0)
	{
		temp = ft_substr(token, var->start, var->c - var->start);
		if (!temp)
		{
			var->var_malloc_flag = true;
			return ;
		}
		if (!process_add(var, temp))
			return ;
	}
	var->start = var->c;
}

bool	split_vars_var(char *token, t_vars_data *var)
{
	char	*temp;

	while (token[var->c])
	{
		if (var->var_malloc_flag)
			return (false);
		temp = NULL;
		if (token[var->c] == '$')
			case_normal(token, var, temp);
		else if (token[var->c] == '?' && token[var->c - 1] == '$')
			case_exit_code(token, var, temp);
		else if (var->c > 0 && (token[var->c - 1] == '$')
			&& ((ft_isdigit(token[var->c]) == 1)
				&& (ft_isdigit(token[var->c + 1]) == 1)))
		{
			case_shell_index(token, var, temp);
		}
		else if (var->var_is_found && (ft_isalnum(token[var->c]) == 0))
			case_allnum(token, var, temp);
		(var->c)++;
	}
	return (true);
}
