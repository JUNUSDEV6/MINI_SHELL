/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:07:35 by clegros           #+#    #+#             */
/*   Updated: 2024/02/07 13:45:47 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex(int argc, char *args[], char *envp[])
{
	t_pipex	pipex;

	if (argc == 5)
	{
		pipex.infile = open(args[1], O_RDONLY);
		if (pipex.infile < 0)
			error();
		pipex.outfile = open(args[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (pipex.outfile < 0)
			error();
		if (pipe(pipex.tube) < 0)
			error();
		pipex.paths = find_path(envp, &pipex);
		if (!pipex.paths)
			error();
		pipex.cmd_paths = ft_split(pipex.paths, ':');
		child_mgmt(pipex, args, envp);
		parent_free(&pipex);
	}
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return ;
}