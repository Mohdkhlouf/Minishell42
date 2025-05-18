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
