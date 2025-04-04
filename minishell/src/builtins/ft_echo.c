#include "../includes/minishell.h"

void	remove_quotes(char *word)
{
	if (word[0] == '"')
		ft_memmove(word, word + 1, ft_strlen(word));
	if (word[ft_strlen(word) - 1] == '"')
		word[ft_strlen(word) - 1] = '\0';
}

int	check_nl(char *new_line)
{
	int	i;

	i = 0;
	if (ft_strlen(new_line) <= 1)
		return (0);
	if (new_line[0] != '-')
		return (0);
	while (new_line[++i])
	{
		if (new_line[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(t_data *data)
{
	int	print_newline;
	int	i;

	print_newline = 1;
	i = 1;
	ft_putstr_fd("\033[1;32m", 1);
	if (data->words[i] && check_nl(data->words[i]))
	{
		print_newline = 0;
		i++;
	}
	while (data->words[i])
	{
		remove_quotes(data->words[i]);
		ft_putstr_fd(data->words[i], 1);
		if (data->words[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (print_newline)
		ft_putchar_fd('\n', 1);
	ft_putstr_fd("\033[0m", 1);
	free_matrix(data->words);
	return (0);
}
