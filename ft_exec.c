/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:06 by clegros           #+#    #+#             */
/*   Updated: 2024/04/09 22:09:09 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	execute_command(char **envp, t_lexer elem)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char	*args[] = {elem.cmd, elem.word, NULL};
		if (execve(elem.cmd, args, envp) == -1)
		{
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
}

void	command_executer(char **envp, t_lexer elem)
{
	(void)envp;
	execute_command(envp, elem);
}
*/