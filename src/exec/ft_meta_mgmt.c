



#include "../../includes/minishell.h"


int	ft_meta_str(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	else if (c == '|')
		return (3);
	else
		return (0);
}

int	list_parkour_str(char *list)
{
	int	i;
	int	j;
	int meta;

	i = 0;
	j = 0;
	meta = 0;
	while (*list != '\0')
	{
		if (ft_meta_str(*list) > 0)
		{
			if (ft_meta_str(*list) == 1)
				meta = 1;
			else if (ft_meta_str(*list) == 2)
				meta = 2;
			else if (ft_meta_str(*list) == 3)
				meta = 3;
			i++;
		}
		list++;
	}
	return (i);
}

/*static int	ft_meta_str(char *c)
{
	if (strcmp(c, "<") == 0)
		return (1);
	if (strcmp(c, ">") == 0)
		return (2);
	if (strcmp(c, "<<") == 0)
		return (3);
	if (strcmp(c, ">>") == 0)
		return (4);
	if (strcmp(c, "|") == 0)
		return (5);
	else
		return (0);
}

static int	list_parkour_str(char *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (list)
	{
		if (ft_meta(list[j++]) > 0)
			i++;
		list++;
		printf("list---%s\n", list);
	}
	return (i);
}*/

void	ft_meta_mgmt(char *cmd, char **envp)
{
	printf("---cmd---%s\n", cmd);
	int		i;

	i = 0;
	t_lexer	*list;

	list = NULL;

	char	*args[100]; // max files ??? 
	int		arg_count;
	arg_count = 0;

	(void)envp;
	//printf("2-2\n");
	tokenize(cmd, &list);
	//printf("1-1\n");
	//print_list(list);
	if (list_parkour(list) >= 1)
	{
		while (list)
		{
			if (list && ft_meta(list->token) == 0)
			{
				//printf("jaaaaa\n");
				if (arg_count <= 100)
					args[arg_count++] = list->token;
				list = list->next;
			}
			else if (list && ft_meta(list->token) > 0)
			{
				list->chr = "m";
				args[arg_count++] = list->token;
				list = list->next;
			}
			//printf("arg%d = %s\n", i, args[i]);
			i++;
		}
		ft_first_iter(args, envp);
	}
}