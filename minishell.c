/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:39:42 by clegros           #+#    #+#             */
/*   Updated: 2024/04/11 16:27:26 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	minishell_loop(char *line, char **envp)
{
	char	**args;
	t_lexer	*list;

//	list.cmd = (char *)malloc(20 * sizeof(char));
//	list.word = (char *)malloc(20 * sizeof(char));
	(void)envp;
	list = NULL;
	list = ((t_lexer *)malloc(sizeof(t_lexer)));
	list->str = NULL;
	ft_set_input_signals();
	while ((line = readline("minishell>>")) != NULL)
	{
		if (!ft_check_quote(line))
			write(2, "Error\n", 6);
		args = &line;
		*args = ft_strchr(*args, 39);
		*args = ft_strchr(*args, 34);
//		while (ft_strchr(*args, '\"') || ft_strchr(*args, '\''))
//		{
//			*args = ft_strtrim(*args, '\"');
//			*args = ft_strtrim(*args, '\''); 
//		}
		printf("%s\n", *args);
		args = ft_split(*args, ' ');
		list = ft_lexero(args, list);
//		printf("%s\n", list->str);
//		printf("%s\n", list->next->str);
		ft_lexer(list);
		while (list)
		{
			printf("----%s----\n", list->str);
			list = list->next;
		}
//		elem = ft_dispatch(line, elem);
//		command_executer(envp, **list);
		free(line);
		free(args);
		line = NULL;
//		if (strcmp(list.cmd, "exit") == 0)
//			break ;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	(void)argc;
	(void)argv;
	line = NULL;
	//signal_handler2(SIGINT);
	minishell_loop(line, envp);
}
