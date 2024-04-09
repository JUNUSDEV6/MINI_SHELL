/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:39:42 by clegros           #+#    #+#             */
/*   Updated: 2024/04/04 13:13:43 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_executer(char **envp, t_element cmd, t_element word)
{
	char	*pipex_args[] = {"./pipex", word.content, cmd.content, "cat", "alles.txt", NULL};
	ft_pipex(5, pipex_args, envp);
}

void	minishell_loop(char *line, char **envp)
{
	t_element	cmd;
	t_element	word;
	t_historic	*hist;

	cmd.content = (char *)malloc(5 * sizeof(char));
	cmd.type = NULL;
	word.content = (char *)malloc(10 * sizeof(char));
	word.type = NULL;
	hist = NULL;
	while ((line = readline("minishell>>")) != NULL)
	{
		add_history(line);
		hist = malloc(sizeof(t_historic));
		hist->content = line;
		ft_dispatch(line, cmd, word, hist);
		hist = hist->next;
		command_executer(envp, cmd, word);
		free(line);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char	*line;
	line = NULL;

	minishell_loop(line, envp);	
}
