/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:17:36 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/02 15:19:45 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "lexing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>




# define SUCCESS 1
# define FAILIURE 0

typedef enum e_token_type
{
	TOK_UNKNOWN,          // Unknown token
	TOK_COMMAND,          // Command (e.g., "ls")
	TOK_ARGUMENT,         // Argument (e.g., "file.txt")
	TOK_PIPE,             // Pipe "|" operator
	TOK_REDIRECT_IN,      // Redirect "<" operator
	TOK_REDIRECT_OUT,     // Redirect ">" operator
	TOK_APPEND,           // Append ">>" operator
	TOK_REDIRECT_HEREDOC, // Here Document "<<" operator
	TOK_SINGLE_QUOTE,     // Single quote "'" character
	TOK_DOUBLE_QUOTE,     // Double quote "\"" character
	TOK_ENV_VAR,          // Environment variable (e.g., $HOME)
	TOK_EOF,              // End of file or input termination

}					t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
}					t_token;

typedef struct s_data
{
	char			*input_line;
	int				cline_parts;
	t_token			*tokens;
	size_t			end;
	size_t			start;
	bool			in_token;
	int				tokens_conter;
	bool			quote_found;
	bool			double_quote_found;
	char			quote_type;
	bool			file_seperator_found;

}					t_data;

void				free_data(t_data *data);
int					line_split(t_data *data);
int					lexing(t_data *data);
int					tokenizing(t_data *data);
void 				print_error(char *msg);
void parsing(t_data *data);

#endif