/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:48:28 by yohanafi          #+#    #+#             */
/*   Updated: 2024/05/17 16:10:09 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_array_print(char **array)
{
	if (!array)
		return ;
	while (*array != NULL)
	{
		printf("|		  {%s}		     |\n", *array);
		array++;
	}
}

// static void	here_txt(char **argv, int *p_fd)
// {
// 	char	*line;

// 	//printf("6");
// 	close(p_fd[0]);
// 	while (1)
// 	{
// 		line = get_next_line(0);
// 		//printf("%s", line);
// 		if (!line)
// 			exit(EXIT_FAILURE);
// 		if (!ft_strncmp(line, argv[2], ft_strlen(argv[2])))
// 		{
// 			//printf("0\n");
// 			//printf("%s\n", line);
// 			free(line);
// 			exit(EXIT_SUCCESS);
// 		}
// 		ft_putstr_fd(line, p_fd[1]);
// 		free(line);
// 	}
// }

// static void	here_doc(char **argv)
// {
// 	pid_t	pid;
// 	int		p_fd[2];
// 	//printf("4");
// 	if (pipe(p_fd) == -1)
// 		exit(1);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(1);
// 	if (!pid)
// 		here_txt(argv, p_fd);
// 	else
// 	{
// 		close(p_fd[1]);
// 		dup2(p_fd[0], 0);
// 		wait(0);
// 	}
// }
static void	exec(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	//printf("jaaa\n");
	char *tmp = ft_strdup(cmd);
	if (list_parkour_str(tmp) >= 1)
		ft_meta_mgmt(tmp, envp);
	else
	{
		//printf("cmd in exec: %s\n", cmd);
	//if (list_parkour_str(cmd) >= 1)
	//{
		s_cmd = ft_split(tmp, ' ');
		if (!s_cmd)
			exit(EXIT_FAILURE);
		path = get_path(*s_cmd, envp);
		if (!path)
			exit(EXIT_FAILURE);
		//printf("------%s\n", *s_cmd);
		//execve(path, s_cmd, envp);
		//printf("path: %s\n", path);
		printf("s_cmd: %s\n", s_cmd[0]);
		//printf(": %s\n", path);
		if (execve(path, s_cmd, envp) == -1)
			exit(EXIT_FAILURE);

	}
}

static void ft_close(int *fd)
{
	close(*fd);
	*fd = -1;
}


static pid_t	ft_pipe(t_cmds *cmd, char **envp, int nb, int argc)
{
	if (nb <= argc - 2)
		if (pipe(cmd->p_fd_output) == - 1)
			exit(1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(1);
	if (cmd->pid == 0)
	{
		if (nb > 0) {
			dup2(cmd->p_fd_input[0], 0);
			close(cmd->p_fd_input[0]);
		}
		if (nb <= argc - 2) {
			dup2(cmd->p_fd_output[1], 1);
			close(cmd->p_fd_output[0]);
			close(cmd->p_fd_output[1]);
		}
		exec(cmd->cmd, envp);
	}
	ft_close(&cmd->p_fd_input[0]);
	ft_close(&cmd->p_fd_output[1]);
	ft_memcpy(cmd->p_fd_input, cmd->p_fd_output, sizeof(cmd->p_fd_input));
	cmd->p_fd_output[0] = -1;
	cmd->p_fd_output[1] = -1;
	return (cmd->pid);
}
/*

-> a chaque fois qu'un programme se termine, il faut que TOUS les fds soient close.
	-> dans child, il faut fermer TOUSSSS les fds avant d'exit(==execve), MEME ceux qu'on n'utilise pas

						cat Makefile 											|						 		grep all  																				|		ls					, prompt reading on 0

timeline -> [enfant]cat ecrit dans fd_output[1], [parent]fd_input = fd_outpu, | [enfant] grep lit dans fd_input[0], ecrit dant fd_ouput[1], [parent]fd_input = fd_output, | ls lit dans fd_input[0]
		
close(0)
int p_fd[2]
pipe(p_fd) - fd_in
			-fd_out
dup2(p_fd[1], 1); <- filled in by cat						dup2(p_fd[0], 0);

*/

void	ft_multi_pipe(int argc, char **argv, char **envp)
{
	int	i;
	// int	fd_out;
	// int	fd_in;
	pid_t	*pid;
	t_cmds	*cmd;
	t_cmds	*head;
	int	status;

	pid = malloc(argc * sizeof(pid_t));
	if (!pid)
		exit(EXIT_FAILURE);
	ft_memset(pid, 0, argc * sizeof(pid_t));
	cmd = malloc(sizeof(t_cmds));
	//head = NULL;
	if (!cmd)
		return ;
	cmd->cmd = NULL;
	cmd->next = NULL;
	cmd->p_fd_input[0] = -1;
	cmd->p_fd_input[1] = -1;
	// if (!ft_strncmp(argv[1], "<<", 2))
	// {
	// 	if (argc < 6)
	// 		exit(0);
	// 	i = 3;
	// 	fd_out = open_file(argv[argc - 1], 2, argv, envp);
	// 	here_doc(argv);
	// }
	// else
	// {
		i = 0;
		// fd_in = 1;
		// fd_out = 1;
		// dup2(fd_in, 0);
	// }
	head = cmd;
	while (i < argc) {
		cmd->cmd = argv[i];
		pid[i] = ft_pipe(cmd, envp, i, argc);
		printf("pid after ft_pipe:%d\n", pid[i]);
		i++;
	}
	cmd = head;

	
	i = 0;
	while (i < argc)
	{
		// ft_putnbr_fd(pid[i], 1);
		// write(1, "\n", 1);
		// printf("pid before waitpid: %d\n", pid[i]);
		waitpid(pid[i], &status, 0);
		i++;
	}
	//kill(i, SIGINT);
}
