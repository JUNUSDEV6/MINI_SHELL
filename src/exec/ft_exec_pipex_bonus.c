/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:48:28 by yohanafi          #+#    #+#             */
/*   Updated: 2024/05/23 17:56:52 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static void	exec(char **cmd, char **envp)
{
	char	*path;
	char	**tmp;
	int		i;

	//printf("------------------------cmd:%s\n", *cmd);
	tmp = cmd;
	i = 0;
	//if (list_parkour_str(cmd) >= 1)
		//ft_meta_mgmt(cmd, envp);
	//if (list_parkour_str(*tmp) >= 1)
	//	ft_meta_mgmt(*tmp, envp);
	//else
	//{
	if (!cmd)
		exit(EXIT_FAILURE);
	path = get_path(*cmd, envp);
	if (!path)
	{
		printf("jai pas de path !!!!!\n");
		exit(EXIT_FAILURE);
	}
	//printf("------%s\n", *s_cmd);
	// write(1, *cmd, ft_strlen(*cmd));
	while(cmd[i])
	{
		printf("x-%s-x\n", cmd[i]);
		ft_strtrim(cmd[i], " ");
		ft_strtrim(cmd[i], "\0");
		ft_strtrim(cmd[i], "\n");
		i++;
	}
	if (execve(path, cmd, envp) == -1){
		printf("PATH FAIL\n\n\n");
		exit(EXIT_FAILURE);
	}
		//if (execve(path, s_cmd, envp) == -1)
			//exit(EXIT_FAILURE);
}
/*!!!!!!!!!!!!!!!!!!!!!je dois faire ca encore!!!!!!!!!!!!!!!!!*/
//static void	here_txt(char *limiter, t_simple_cmds *cmd)
//{
//	char	*line;
//	(void)cmd;
//
//	//printf("6");
//	while (1)
//	{
//		line = get_next_line(0);
//		//printf("%s", line);
//		if (!line)
//			exit(EXIT_FAILURE);
//		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
//		{
//			//printf("0\n");
//			//printf("%s\n", line);
//			free(line);
//			exit(EXIT_SUCCESS);
//		}
//		//ft_putstr_fd(line, cmd->p_fd[1]);
//		free(line);
//	}
//}

//static void	here_doc(char **argv)
//{
//	pid_t	pid;
//	int		p_fd[2];
//	//printf("4");
//	if (pipe(p_fd) == -1)
//		exit(1);
//	pid = fork();
//	if (pid == -1)
//		exit(1);
//	if (!pid)
//		here_txt(argv, p_fd);
//	else
//	{
//		close(p_fd[1]);
//		dup2(p_fd[0], 0);
//		wait(0);
//	}
//}
static void ft_close(int *fd)
{
	close(*fd);
	*fd = -1;
}

// Function to trim leading whitespace
static char *ltrim(char *str) {
    while (isspace((unsigned char)*str)) str++;
    return str;
}

// Function to trim trailing whitespace
static char *rtrim(char *str) {
    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    return str;
}

// Function to trim leading and trailing whitespace
static char *trim(char *str) {
    return rtrim(ltrim(str));
}
static void	ft_check_redirection(t_simple_cmds *cmd, int fd)
{
	if (!cmd)
		return ;
	if (!ft_strncmp(cmd->redirections->token, ">", 1) && ft_strlen(cmd->redirections->token) == 1){
	
		fd = open(trim(cmd->redirections->next->token), O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd, 1);}
	if (!ft_strncmp(cmd->redirections->token, ">>", 2) && ft_strlen(cmd->redirections->token) == 2){

		fd = open(trim(cmd->redirections->next->token), O_WRONLY | O_CREAT | O_APPEND, 0777);
		dup2(fd, 1);}
	if (!ft_strncmp(cmd->redirections->token, "<", 1) && ft_strlen(cmd->redirections->token) == 1){

		fd = open(trim(cmd->redirections->next->token), O_RDONLY, 0777);
		dup2(fd, 0);}
	//if (!ft_strncmp(cmd->redirections->token, "<<", 1) && ft_strlen(cmd->redirections->token) == 2){
	//	here_txt(cmd->redirections->next->token, cmd);
	//}
	if (fd == - 1)
	{
		write(2, cmd->redirections->next->token, ft_strlen(cmd->redirections->next->token));
		write(2, "-error-\n", 8);
		exit(0);
	}
}


static pid_t	ft_pipe(t_simple_cmds *cmd, char **envp, int nb, int argc)
{
	pid_t	pid;
	int		fd = 0;
	printf("cmd->str ----------: %d - %s\n", nb, *cmd->str);
	//printf("nb = %d ----- argc = %d\n\n", nb, argc);
	// derniere modification
	if (nb < argc)
		if (pipe(cmd->p_fd_output) == - 1)
			exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		//printf("ARRive ici avant exec\n");
		if (nb > 0) {
			// printf("icicic\n\n");
			dup2(cmd->p_fd_input[0], 0);
			close(cmd->p_fd_input[0]);
		}
		if (nb < argc) {
			dup2(cmd->p_fd_output[1], 1);
			close(cmd->p_fd_output[0]);
			close(cmd->p_fd_output[1]);
		}
		if (cmd->redirections)
		{
			ft_check_redirection(cmd, fd);
			//fd = open(cmd->redirections->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			//dup2(fd, 1);
		}
		// write(2, *cmd->str, ft_strlen(*cmd->str));
		exec(cmd->str, envp);
	}
	ft_close(&cmd->p_fd_input[0]);
	ft_close(&cmd->p_fd_output[1]);
	if (cmd->next) {
		ft_memcpy(cmd->next->p_fd_input, cmd->p_fd_output, sizeof(cmd->p_fd_input));
	}
	cmd->p_fd_output[0] = -1;
	//cmd->p_fd_output[1] = -1;
	return (pid);
}



void	ft_multi_pipe(int argc, t_simple_cmds *list, char **envp)
{
	int	i;
	int 	status;
	pid_t	*pid;

	//printf("-------1-------\n");
	i = 0;
	pid = malloc((argc + 1) * sizeof(pid_t));
	if (!pid)
		exit(EXIT_FAILURE);
	ft_memset(pid, 0, (argc + 1) * sizeof(pid_t));
	list->p_fd_input[0] = -1;
	list->p_fd_input[1] = -1;
	if (!ft_strncmp(list->str[1], "heredoc", 7))
	{
		//printf("1");
		if (argc < 6)
			exit(0);
		i = 3;
		//printf("1");
		//fd_out = open_file(list->str[argc - 1], 2, list->str, envp);
		//printf("3");
		//here_doc(list->str);
	}
	//printf("valeur de argc %d\n\n\n", argc);
	while (i <= argc)
	{
		//write(2, "test\n", 5);
		// printf("cmd->str ----------: %s\n", *list->str);
		//printf("1 dans le while i < argc, i = %d ,,, argc = %d\n\n", i, argc);
		pid[i] = ft_pipe(list, envp, i, argc);
		if (list->next)
			list = list->next;
		i++;
	}
	i = 0;
	while (pid[i])
		waitpid(pid[i++], &status, 0);
	// while (i <= argc)
	// {
	// 	// ft_putnbr_fd(pid[i], 1);
	// 	// write(1, "\n", 1);
	// 	// printf("pid before waitpid: %d\n", pid[i]);
	// 	waitpid(pid[i], &status, 0);
	// 	i++;
	// }
	// dup2(fd_out, 1);
	// exec(argv[argc - 1], envp);
}