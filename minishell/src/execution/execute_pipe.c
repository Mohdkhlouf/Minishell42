#include "../includes/minishell.h"

void execute_child(t_data *data, t_parsed_data *cmds_d, int i, int *prev_cmd, int *pipe_fd)
{
    char *path;

    if (*prev_cmd != -1)
    {
        dup2(*prev_cmd, STDIN_FILENO); 
        close(*prev_cmd);
    }
    if (i < cmds_d->cmds_counter - 1)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]); 
    }
    set_default_signal_handlers(); // Set up signal handling
    path = find_path(data, cmds_d->cmds[i].cmd[0]); // Find the path of the command
    if (!path)
    {
        printf("command not found: %s\n", cmds_d->cmds[i].cmd[0]);
        exit(127); // Command not found, exit with 127
    }
    execve(path, cmds_d->cmds[i].cmd, data->envp); 
    free(path); 
    perror("execve failed");
    return;
}

void execute_parent(int *prev_cmd, int *pipe_fd, int i, int cmds_counter)
{
    if (*prev_cmd != -1)
        close(*prev_cmd);
    if (i < cmds_counter - 1)
    {
        close(pipe_fd[1]);
        *prev_cmd = pipe_fd[0];
	}
}

void execute_pipes(t_data *data, t_parsed_data *cmds_d, int i, int *prev_cmd)
{
	int pipe_fd[2];
	pid_t pid;

	if(i < cmds_d->cmds_counter && pipe(pipe_fd) == -1)
	{
		perror("pipe");
        return;
	}
	pid = fork(); //create a child process
	if(pid == -1)
	{
		perror("fork");
		return;
	}
	else if(pid == 0) // child process
		execute_child(data, cmds_d, i, prev_cmd, pipe_fd);
	else
		execute_parent(prev_cmd, pipe_fd, i, cmds_d->cmds_counter);
}

