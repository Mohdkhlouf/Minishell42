
#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_data	t_data;
typedef struct s_parsed_data t_parsed_data;

void execution(t_data *data, t_parsed_data *cmds_d);

#endif