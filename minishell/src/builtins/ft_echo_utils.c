
//#include "../includes/minishell.h"

// static char *get_env_value(t_var *node, const char *key)
// {
// 	while (node)
// 	{
// 		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0)
// 			return (node->value);
// 		node = node->next;
// 	}
// 	return (NULL);
// }

// void check_echo_$(t_data *data)
// {
// 	char *name;
// 	int i = 1;
// 	while (data->words[i])
// 	{
// 		int checksign = ft_strncmp(data->words[i], "$", ft_strlen("$"));
// 		if (checksign == 0)
// 		{
// 			name = ft_substr(data->words[i], 1, ft_strlen(data->words[i]) - 1);
// 			char *value = get_env_value(data->env_lst, name);
// 			if (value)
// 				printf("%s", value);
// 		}
// 		i++;
// 	}
// }
// int check$(char *sign)
// {
// 	char *has_value = ft_strchr(sign, '$');
// 	if (has_value)
// 		return (1);
// 	return (0);
// }
