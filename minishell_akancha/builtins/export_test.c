#include "../main.h"

int getSize(t_var *env)
{
	int count = 0;
	while (env->next)
	{
		count++;
		env = env->next;
	}
	return (count + 1);
}

char **populate_strings(t_var *env)
{
	int i;
	char **strings;

	i = 0;
	strings = malloc(sizeof(char *) * (getSize(env) + 1));
	while (env)
	{
		strings[i] = ft_strdup(env->key);
		env = env->next;
		i++;
	}
	strings[i] = NULL;
	return (strings);
}

char **sort_list(t_var *env)
{
	char **strings;
	int i;
	int flag;
	char *temp;

	flag = 1;
	strings = populate_strings(env);
	while (flag)
	{
		i = 0;
		flag = 0;
		while (strings[i])
		{
			if (strings[i + 1] != NULL && ft_strncmp(strings[i], strings[i + 1], ft_strlen(strings[i + 1])) > 0)
			{
				flag = 1;
				temp = strings[i];
				strings[i] = strings[i + 1];
				strings[i + 1] = temp;
			}
			i++;
		}
	}
	return (strings);
}

void print_exported(t_var *env, t_data *data)
{
	t_var *copy;
	char **array;
	int i;

	i = 0;
	if (!env)
		return;
	copy = env;
	array = sort_list(copy);
	while (array[i])
	{
		printf("declare -x %s", array[i]);
		if (get_env_value(array[i], data) && get_env_value(array[i], data)[0] != '\0')
		{
			printf("=\"%s\"", get_env_value(array[i], data));
		}
		printf("\n");
		i++;
	}
}

int ft_export1(t_data *data)
{
	t_var *env;

	env = data->env_lst;
	if (!data->words[1])
		print_exported(env, data);
	return (0);
}
