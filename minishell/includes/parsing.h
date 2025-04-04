#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_data	t_data;



typedef struct s_cmds
{
	char				**cmd;
	char				**reds;
}						t_cmds;

typedef struct s_parsed_data
{
	t_cmds				*cmds;
	int 				cmds_counter;
	int 				pipes_counter;
	int	cmds_ctr;
	int	red_ctr;
	int	token_ctr;
}						t_parsed_data;


void					parsing(t_data *data, t_parsed_data *cmds_d);
void	cmds_process_loop(t_data *data, t_parsed_data *cmds_data);

#endif