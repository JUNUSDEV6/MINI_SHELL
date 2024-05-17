/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:39:42 by clegros           #+#    #+#             */
/*   Updated: 2024/05/17 16:01:53 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

static void	signal_handler2(int signo)
{
	if (signo == SIGINT)
		ft_putendl_fd("", 1);
}

void	minishell_loop(char **envp)
{
	char	**args;
	char	*line;
	t_lexer	*list;
	t_pipex	exec;

	(void)envp;
	line = NULL;
	list = NULL;
	list = ((t_lexer *)malloc(sizeof(t_lexer)));
	list->str = NULL;
	exec.paths = find_path(envp, &exec);
	exec.cmd_paths = ft_split(exec.paths, ':');
	exec.cmd = NULL;
//	signal(SIGCHLD, SIG_IGN);
	while (1)
	{
		// printf("before =====> |%s|\n", line);
		//printf("before :|%s|\n", line);
		ft_set_input_signals();
		line = readline("minishell>>");
		signal(SIGINT, &signal_handler2);
		// printf("after =====> |%s|\n", line);
		if (!line)
		{
			printf("I'M EXITING BUECAUSE I'M UGGLY\n");
			break ;
		}
		add_history(line);
		if (!ft_check_quote(line))
		{
			write(1, "Error\n", 6);
			free(line);
		}
		char *tmp = ft_strdup(line);
		args = ft_split(tmp, '|');
		if (!args)
			exit(9);
		list = ft_lexero(args, list);
		if (list)
		{
			exec = ft_dispatch(exec, list->str);
			//if(ft_check_hrdoc(args) == 1)
			//{
			//	return ;
			//}
			//else
			command_executer(args, envp, list, exec);
		}
		/*
		ft_lexer(list);
		ft_parser(list);
		*/
		/*while (list)
		{
			printf("f0ff----%s----|----%d----|----%s----\n", list->str, list->i, list->chr);
			list = list->next;
		}*/
		free(list);
		free(line);
		//free(args);
		//args = NULL;
		//line = NULL;
//		if (strcmp(list.cmd, "exit") == 0)
//			break ;
//		system("leaks ./minishell");
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	//char	*line;

	(void)argc;
	(void)argv;
	//line = malloc(sizeof(char *));
	//line = NULL;
	//signal_handler2(SIGINT);
	minishell_loop(envp);
}
