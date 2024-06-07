/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:05:23 by clegros           #+#    #+#             */
/*   Updated: 2024/06/05 16:58:13 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_tokens(t_lexer *tokens)
{
	int		count;
	t_lexer	*temp;

	count = 0;
	temp = tokens;
	while (temp != NULL && ft_strncmp(temp->token, "|", 1) != 0)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static void	fill_command_strings(t_lexer **tokens, t_simple_cmds *new_cmd)
{
	t_lexer	*current;
	int		i;

	current = *tokens;
	i = 0;
	while (current != NULL && strcmp(current->token, "|") != 0)
	{
		ft_strtrim(current->token, " ");
		new_cmd->str[i++] = current->token;
		current = current->next;
	}
	new_cmd->str[i] = NULL;
	*tokens = current;
}

void	parse_command(t_lexer **tokens, t_simple_cmds **cmd_list)
{
	t_lexer			*current;
	t_lexer			*cmd_start;
	t_lexer			*redirections;
	t_simple_cmds	*new_cmd;
	int				token_count;

	current = *tokens;
	cmd_start = current;
	redirections = NULL;
	new_cmd = create_simple_cmd_node();
	token_count = count_tokens(current);
	new_cmd->str = (char **)malloc(sizeof(char *) * (token_count + 1));
	parse_redirections(&cmd_start, &redirections);
	if (new_cmd->str == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	fill_command_strings(&current, new_cmd);
	new_cmd->redirections = redirections;
	add_spl_cmd(cmd_list, new_cmd);
	if (current != NULL && strcmp(current->token, "|") == 0)
		*tokens = current->next;
	else
		*tokens = current;
}
