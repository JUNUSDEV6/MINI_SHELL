/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:06:04 by clegros           #+#    #+#             */
/*   Updated: 2024/02/07 13:42:45 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.infile, STDIN_FILENO);
	if (pipex.infile == -1)
		error();
	dup2(pipex.tube[1], STDOUT_FILENO);
	close(pipex.tube[0]);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = parsing(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
		error();
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.outfile, STDOUT_FILENO);
	if (pipex.outfile == -1)
		error();
	dup2(pipex.tube[0], STDIN_FILENO);
	close(pipex.tube[1]);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = parsing(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
		error();
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	child_mgmt(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return ;
}
