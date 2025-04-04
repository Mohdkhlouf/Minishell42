#include "../includes/minishell.h"

void	export_with_param(t_data *data)
{
	char	*param_value;
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	param_value = data->words[1];
	if (ft_isalpha(param_value[0]) || param_value[0] == '_')
	{
		int value = ft_strcmp("=", &param_value[i]);
		printf("value is :%d\n", value);
		if (!ft_strcmp("=", &param_value[i]))
		{
			printf("hello.\n");
			str = ft_split(param_value, '=');
			if (!str)
				return ;
			while (str[i][j])
			{
				if (ft_isalnum(str[i][j]) || str[i][j] == '_')
				{
					//TODO
					//update env if exist
					//add if not exits
					//add to export in the end

					if(get_env_value(str[i], data))
					{
						printf("exits");
					}
					else
						printf("NOT EXITS");
				}
				else
					printf("export: \"%s\": not a valid identifier\n",
						param_value);
				j++;
			}
		}
		else
		{
			//TODO
			//add to export if not exist
		}
	}
	else
		printf("export: \"%s\": not a valid identifier\n", param_value);
}
