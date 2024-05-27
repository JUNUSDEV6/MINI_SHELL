/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:05:23 by clegros           #+#    #+#             */
/*   Updated: 2024/05/15 16:18:05 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirection_token(t_lexer **tokens, t_lexer **redirections,
		t_lexer **current, t_lexer **prev)
{
	t_lexer	*next_token;

	next_token = (*current)->next;
	if (*prev == NULL)
		*tokens = next_token;
	else
		(*prev)->next = next_token;
	(*current)->next = *redirections;
	*redirections = *current;
	*current = next_token;
	if (*current != NULL)
	{
		next_token = (*current)->next;
		if (*prev == NULL)
			*tokens = next_token;
		else
			(*prev)->next = next_token;
		(*current)->next = *redirections;
		*redirections = *current;
		*current = next_token;
	}
}
/*static void	here_txt(char *argv, int *p_fd)
{
	char	*line;

	//printf("6");
	close(p_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		//printf("%s", line);
		if (!line)
			exit(EXIT_FAILURE);
		if (!ft_strncmp(line, argv, ft_strlen(argv)))
		{
			//printf("0\n");
			printf("line %s\n", line);
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, p_fd[1]);
		free(line);
	}
}

static void	here_doc(char *argv)
{
	pid_t	pid;
	int		p_fd[2];
	//printf("4");
	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
		here_txt(argv, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(0);
	}
}*/
void	parse_redirection_tokens(t_lexer **tokens, t_lexer **redirections)
{
	t_lexer	*current;
	t_lexer	*prev;

	current = *tokens;
	prev = NULL;
	while (current != NULL && ft_strncmp(current->token, "|", 1) != 0)
	{
		ft_strtrim(current->token, " ");
		if (is_redirection_token(current->token) == 0)
			handle_redirection_token(tokens, redirections, &current, &prev);
		else if (is_redirection_token(current->token) == 1)
		{
			handle_redirection_token(tokens, redirections, &current, &prev);
			/*current = current->next;
			printf("current token %s\n", current->token);				---heredoc---
			here_doc(current->token);*/
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	parse_redirections(t_lexer **tokens, t_lexer **redirections)
{
	parse_redirection_tokens(tokens, redirections);
	reverse_redirections_list(redirections);
}

void	parse_command(t_lexer **tokens, t_simple_cmds **cmd_list)
{
	t_lexer			*current;
	t_lexer			*cmd_start;
	t_lexer			*redirections;
	t_simple_cmds	*new_cmd;
	int				token_count;
	t_lexer			*temp;
	int				i;

	current = *tokens;
	cmd_start = current;
	redirections = NULL;
	new_cmd = create_simple_cmd_node();
	token_count = 0;
	i = 0;
	parse_redirections(&cmd_start, &redirections);
	temp = current;
	while (temp != NULL && ft_strncmp(temp->token, "|", 1) != 0)
	{
		token_count++;
		temp = temp->next;
	}
	new_cmd->str = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (new_cmd->str == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (current != NULL && strcmp(current->token, "|") != 0)
	{
		ft_strtrim(current->token, " ");
		new_cmd->str[i++] = current->token;
		current = current->next;
	}
	new_cmd->str[i] = NULL;
    /*if (new_cmd->str[0] != NULL && is_builtin(new_cmd->str[0])) {
        // Assign the corresponding function pointer to new_cmd->builtin
        // Example: new_cmd->builtin = &builtin_function;
    }*/
	new_cmd->redirections = redirections;
	add_simple_cmd_node(cmd_list, new_cmd);
	if (current != NULL && strcmp(current->token, "|") == 0)
		*tokens = current->next;
	else
		*tokens = current;
}
