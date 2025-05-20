#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"
# include <stdbool.h>
# define DELEMETERS " \t\n\0"
# define VAR_DELEMITER "/\'\"$"

typedef struct s_data	t_data;

typedef struct s_vars_data
{
	char				**vars_arr;
	char				*var_var;
	char				*temp;
	int					parts_count;
	int					vars_count;
	int					len;
	bool				var_is_found;
	int					start;
	int					c;
	bool				var_malloc_flag;
}						t_vars_data;

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
bool					path_set_and_join(t_data *data, int i,
							t_vars_data *var);
void					search_for_file_seperator(t_data *data, t_var_d *var,
							int i);
bool					var_init(t_vars_data *var, t_data *data, int i);
bool					var_handler2(t_data *data, int i);
void					print_tokens(t_data *data);
void					free_var(t_vars_data *var);
int						assign_quotes(t_data *data, int len, int i, char *temp);
bool					quote_fixing(t_data *data, int i);
void					redirection_setting(t_data *data, int i);
void					free_var(t_vars_data *var);
void					append_eof_token(t_data *data, int type);
void					ft_free(char *str);
bool					split_vars(t_data *data, char *token, t_vars_data *var);
bool					split_vars_var(char *token, t_vars_data *var);
bool					process_add(t_vars_data *var, char *temp);
bool					quotes_tekonizing(t_data *data, int i);
bool					var_handler_token(t_data *data, int i);
void					var_handler_quotes_token(t_data *data, int i);
bool					set_exit_value(t_data *data, int i);
bool					init_var_handler(t_data *data, int *i);

#endif