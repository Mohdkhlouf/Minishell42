#include "../main.h"

void export_with_param(t_data *data)
{
	char *param_value;
	char **str;
	int i = 0;
	int j = 0;
	param_value = data->words[1];
	if (ft_isalpha(param_value[0]) || param_value[0] == '_')
	{
		if (!ft_strcmp("=", &param_value[i]))
		{
			str = ft_split(param_value, '=');
			if (!str)
				return;
			while (str[i][j])
			{
				if (ft_isalnum(str[i][j]) || str[i][j] == '_')
				{
				}
				else
					printf("export: \"%s\": not a valid identifier\n", param_value);
				j++;
			}
		}
		else
		{
		}
	}
	else
		printf("export: \"%s\": not a valid identifier\n", param_value);
}
