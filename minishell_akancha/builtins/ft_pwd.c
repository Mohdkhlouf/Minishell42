#include "../main.h"

int ft_pwd(t_data *data)
{
	if (data->words[0] && data->words[1])
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		perror("getcwd failed");
		return (1);
	}
	ft_putendl_fd(data->pwd, 1);
	free(data->pwd);
	return (0);
}
