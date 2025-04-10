
#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_data			t_data;
typedef struct s_parsed_data	t_parsed_data;
typedef struct s_cmds 			t_cmds;

void							execution(t_data *data, t_parsed_data *cmds_d);
bool							is_empty_cmd(t_cmds cmd);
void							execute_command(t_cmds cmd, t_data *data);
void							parse_path(t_data *data);


#endif