/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:12:23 by akumari           #+#    #+#             */
/*   Updated: 2025/05/21 13:16:36 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	closing_heredoc(int fd)
{
	close(fd);
	reset_signals_to_prompt();
	rl_event_hook = NULL;
}
