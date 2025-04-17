#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"
# include <stdbool.h>
# define DELEMETERS " \t\n\0"
# define VAR_DELEMITER "/\'\"$"

typedef struct s_data	t_data;

// for var when it is double quoted
typedef struct s_vars_data
{
	char				**vars_arr;
	int					parts_count;
	int					vars_count;
	char				*temp;
	char				*var_var;
	int					len;
	bool				var_is_found;
}						t_vars_data;

// for var when it is single one
typedef struct s_var_d
{
	char				*path;
	char				*var;
	char				*temp;
	int					len;
	int					j;
}						t_var_d;

void					space_function(t_data *data);
void					pipe_function(t_data *data);
void					redirectin_function(t_data *data);
void					redirectout_function(t_data *data);
void					append_token_double(t_data *data, int type);
void					normal_function(t_data *data);
void					append_token(t_data *data, int type);
void					env_variable_function(t_data *data);
void					eof_function(t_data *data);
int						find_vars_count(t_data *data, int i);
void					path_set_and_join(t_data *data, int i, char *temp,
							char *path);
void					search_for_file_seperator(t_data *data, t_var_d *var,
							int i);
void					var_init(t_vars_data *var, t_data *data, int i);
void					var_handler2(t_data *data, int i);
void					print_tokens(t_data *data);
void					free_var(t_vars_data *var);
void					assign_quotes(t_data *data, int len, int i, char *temp);
void					quote_fixing(t_data *data, int i);
void					redirection_setting(t_data *data, int i);
void					free_var(t_vars_data *var);

#endif