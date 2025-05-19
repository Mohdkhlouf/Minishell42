#include "../includes/minishell.h"

char	*join_cmd_with_slash(char *cmd)
{
	char	*result;

	result = NULL;
	result = ft_strjoin("/", cmd);
	if (!result)
		print_error("Join is not done\n");
	return (result);
}

char	*find_path(t_data *data, char *cmd)
{
	int	i;
	int	not_found;

	not_found = 0;
	i = 0;
	data->file_name = NULL;
	data->with_slash = join_cmd_with_slash(cmd);
	if (!data->parsed_path)
		return (free(data->with_slash), NULL);
	while (data->parsed_path[i])
	{
		if (i != 0)
			ft_free(data->file_name);
		data->file_name = ft_strjoin(data->parsed_path[i], data->with_slash);
		if (!data->file_name)
			print_error("Join is not done\n");
		if ((access(data->file_name, F_OK) == 0))
			return (free(data->with_slash), data->file_name);
		else
			not_found = 1;
		i++;
	}
	if (not_found == 1)
		free(data->file_name);
	return (free(data->with_slash), NULL);
}

void	free_2d_cmd_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_cmd(t_cmds *cmd)
{
	free_2d_cmd_arr(cmd->cmd);
	free_2d_cmd_arr(cmd->reds);
}