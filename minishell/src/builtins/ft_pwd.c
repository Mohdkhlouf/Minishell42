#include "../includes/minishell.h"

int	ft_pwd(t_data *data)
{
	if (data->words[0] && data->words[1])
	{
		printf("\033[0;31mpwd: too many arguments\033[0m\n");
		return (1);
	}
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		perror("getcwd failed");
		return (1);
	}
	printf("\033[0;32m%s\033[0m\n", data->pwd);
	free(data->pwd);
	return (0);
}
