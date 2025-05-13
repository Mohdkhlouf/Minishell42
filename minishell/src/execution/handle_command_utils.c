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
	int		i;
	char	*file_name;
	char	*with_slash;
	int		not_found;

	not_found = 0;
	i = 0;
	file_name = NULL;
	with_slash = join_cmd_with_slash(cmd);
	if (!data->parsed_path)
		return (free(with_slash), NULL);
	while (data->parsed_path[i])
	{
		if (i != 0)
			ft_free(file_name);
		file_name = ft_strjoin(data->parsed_path[i], with_slash);
		if (!file_name)
			print_error("Join is not done\n");
		if ((access(file_name, F_OK) == 0))
			return (free(with_slash), file_name);
		else
			not_found = 1;
		i++;
	}
	if (not_found == 1)
		free(file_name);
	return (free(with_slash), NULL);
}

/*to handlle any empty cmd*/
void	handle_empty_cmd(t_cmds *cmd, t_data *data)
{
	(void)data;
	(void)cmd;
	printf("empty cmd handler\n");
}
