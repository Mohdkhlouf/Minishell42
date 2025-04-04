/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:03:50 by akumari           #+#    #+#             */
/*   Updated: 2025/03/25 13:12:51 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX 100000

# define SUCCESS 1
# define FAILURE 0

# include "../Libft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_env
{
    char            *key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_mini
{
    t_env *env;
}   t_mini;

int					ft_pwd(void);
int		ft_env(t_mini *mini);
#endif