#include "../includes/minishell.h"

void	heredoc_handller(int *i, char *delimiter)
{
	int heredoc[2];
	char	*line;
	char	*heredoc_content;
	char	*temp;
	char	*final_joined;

	if(pipe(heredoc)== -1)
	{
		perror("pipe");
		return ;
	}	
	heredoc_content =  ft_strdup("");
	while(1)
	{
		line = readline("heredoc> ");
		if(!line)
		{
			close(heredoc[1]);
   			break;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(heredoc[1]);
			break;
		}
		temp = ft_strjoin(line, "\n");
		if(!temp)
		{
			free(heredoc_content);
			free(line);
			return;
		}
		free(line);
		final_joined = ft_strjoin(heredoc_content, temp);
		if(!final_joined)
		{
			free(heredoc_content);
			free(temp);
			return;
		}
		free(heredoc_content);
		free(temp);
		heredoc_content = final_joined;
	}
	if (heredoc_content)
	{
		write(STDOUT_FILENO, heredoc_content, ft_strlen(heredoc_content));
		write(heredoc[1], heredoc_content, ft_strlen(heredoc_content));
		free(heredoc_content);
	}
	close(heredoc[1]);
	dup2(heredoc[0], STDIN_FILENO);
	close(heredoc[0]);
	(*i)++;
}


// void child_heredoc(int *heredoc, char *delimiter)
// {
// 	char	*line;
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// 	close(heredoc[0]);
// 	while(1)
// 	{
// 		line = readline("heredoc> ");
// 		if(!line)
// 		{
// 			close(heredoc[1]);
//    			exit(0);
// 		}
// 		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
// 		{
// 			free(line);
// 			close(heredoc[1]);
// 			exit(0);
// 		}
// 		write(heredoc[1], line, ft_strlen(line));
//         write(heredoc[1], "\n", 1);
// 		free(line);
// 	}
// }

// void	heredoc_handller(int *i, char *delimiter)
// {
// 	int pid;
// 	int heredoc[2];
// 	int j;
	

// 	j = pipe(heredoc);
// 	if(j == -1)
// 	{
// 		perror("pipe");
// 		return ;
// 	}	
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return ;
// 	}
// 	else if(pid == 0)
// 	{
// 		child_heredoc(heredoc, delimiter);
// 	}
// 	else
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		close(heredoc[1]);
// 		wait(NULL);
// 		close(heredoc[0]);
// 	}
// 	(*i)++;
// }
