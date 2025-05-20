#include "../includes/minishell.h"


/*testing function to print commands and redirections*/
void	printing_cmds_reds(t_parsed_data *cmds_d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("i have %d commands\n", cmds_d->cmds_counter);
	while (i < cmds_d->cmds_counter)
	{
		j = 0;
		printf("Final Command %d: ", i);
		while (cmds_d->cmds[i].cmd[j])
		{
			printf("%s ", cmds_d->cmds[i].cmd[j]);
			j++;
		}
		printf("#\n");
		printf("Final reds %d: ", i);
		j = 0;
		if (cmds_d->cmds[i].reds[j] && cmds_d->cmds[i].reds)
		{
			while (cmds_d->cmds[i].reds[j])
			{
				printf("%s ", cmds_d->cmds[i].reds[j]);
				j++;
			}
		}
		else
		{
			printf("No reds");
		}
		printf("#\n");
		i++;
	}
}

void	print_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i].data && i < data->tokens_conter)
	{
		printf("Token:#%s# Type:%u\n", data->tokens[i].data,
			data->tokens[i].type);
		i++;
	}
}


// void	free_var_handler(t_data *data, t_vars_data *var)
// {
// 	if (!var)
// 		return ;
// 	(void)data;
// 	// if (var->vars_arr)
// 	// {
// 	// 	for (int i = 0; i < data->tokens_conter; i++)
// 	// 		free(var->vars_arr[i]);  // 🔥 This is the key fix
// 	// }
// 	free(var->var_var);
// 	free(var);
// }