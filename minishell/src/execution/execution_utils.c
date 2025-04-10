#include "../includes/minishell.h"

/*this function tests if the function is empty then print and return value. it needs more later*/
bool	is_empty_cmd(t_cmds cmd)
{
	if (ft_strcmp(cmd.cmd[0], "") == 0)
	{
		/*print_error("Command not found.\n");*/
		return (true);
	}
	return (false);
}

/* this function make 2d array for path value from env.
this valuse to if the commands sent is existed or not by comparing it with the values in the path value*/

void	parse_path(t_data *data)
{
	printf("PATH is:%s\n", data->path);
	// if (data->path)
	// {
	// 	data->parsed_path = ft_split(data->path, ':');
	// 	if (!data->parsed_path)
	// 	{
	// 		print_error("Error while mallocating memoery\n");
	// 		exit(1);
	// 	}
	// }
}


// char	*find_path(t_pipex *pipex, char *cmd)
// {
// 	int		i;
// 	char	*file_name;
// 	int		not_found;

// 	not_found = 0;
// 	i = 0;
// 	file_name = NULL;
// 	while (pipex->env_path[i])
// 	{
// 		if (i != 0)
// 			free(file_name);
// 		file_name = ft_strjoin(pipex->env_path[i], cmd);
// 		if (!file_name)
// 			exit_print_error(pipex);
// 		if ((access(file_name, F_OK) == 0))
// 			return (file_name);
// 		else
// 			not_found = 1;
// 		i++;
// 	}
// 	if (not_found == 1)
// 		path_nfnound_error(pipex, file_name, cmd);
// 	return (NULL);
// }
