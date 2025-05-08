#include "../includes/minishell.h"

void get_export(char **sorted_arr, t_data *data)
{
	int i;

	i = 0;
	while (sorted_arr[i])
	{
		printf("declare -x %s", sorted_arr[i]);
		if (get_env_value(sorted_arr[i], data) && get_env_value(sorted_arr[i], data)[0] != '\0')
		{
			printf("=\"%s\"", get_env_value(sorted_arr[i], data));
		}
		printf("\n");
		i++;
	}
}
