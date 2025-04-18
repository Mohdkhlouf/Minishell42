#include "../includes/minishell.h"

/*reset the signals from child process*/
void set_default_signal_handlers(void)
{
    struct sigaction sa;

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}


/* main function to execute one command, i will make it execute the redirections
then do the command execution*/
void exec_cmd(t_cmds *cmd, t_data *data)
{
	(void)data;
	char *path;

	path = NULL;
	set_default_signal_handlers();
	path = find_path(data, cmd->cmd[0]);
	if(!path)
		return;
	if (execve(path, cmd->cmd, data->envp) == -1)
		return;
	free(path);
}

/* this function will start the fork to execute the cmd
i did the fork here.
then send the execution to child process*/
int	execute_cmd(t_cmds *cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("ERROR IN FORKING\n");
		exit(1);
	}
		
	if (pid == 0)
		exec_cmd(cmd, data);
	return (pid);
}

/*this function recieved a cmd struct, first i check if the command is empty
then if not, check if it is a built in, then will execute as built in.
if not, i use another function to start executing the external cmd*/
void	handle_command(t_cmds *cmd, t_data *data)
{
	int	ret;
	int pid;
	int status;

	ret = 0;
	pid = 0;
	(void)data;
	if (!is_empty_cmd(cmd))
	{
		if (is_builtin(cmd->cmd[0]) == 1)
		{
			/*function to execute builtin function the sent will be a command*/
			ret = execute_builtin(data, cmd);
			if(ret == -1)
				print_error("Error.\n");
			printf("execute builtin \n");
		}
		else
		{
			execute_redirections(data, cmd);
			pid = execute_cmd(cmd, data);
			waitpid(pid, &status, 0);
		}
	}
	else
		handle_empty_cmd(cmd, data);
	
}
