/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:40:14 by yohanafi          #+#    #+#             */
/*   Updated: 2024/04/17 17:43:16 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_quote(char *str)
{
	int i = 0;
    bool double_flag = true;
    bool single_flag = true;
    bool in_double_quotes = false;
    bool in_single_quotes = false;

    while (str[i])
    {
        if (str[i] == DOUBLE_QUOTE && !in_single_quotes)
            in_double_quotes = !in_double_quotes;

        if (str[i] == QUOTE && !in_double_quotes)
            in_single_quotes = !in_single_quotes;

        i++;
    }
    double_flag = !in_double_quotes;
    single_flag = !in_single_quotes;

    return (double_flag && single_flag);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
}

static bool	ft_lexer_token(char c)
{
	if (c == QUOTE || c == DOUBLE_QUOTE)
		return (true);
	if (c == PIPE_LINE)
		return (true);
	if (c == REDIR_IN || c == REDIR_OUT)
		return (true);
	return (false);
}

static void	ft_stock_token(char *c, t_lexer *lexer)
{
	lexer->chr = *c;
//	printf("---%c---\n", lexer->chr);
	lexer = lexer->next;
}

static void	ft_scan(t_lexer *lexer)
{
	char	*ptr;

	while (lexer != NULL)
	{
		//printf("--0--\n");
		ptr = lexer->str;
		while (*ptr != '\0')
		{
			//printf("--1--\n");
			if (ft_lexer_token(*ptr))
				ft_stock_token(ptr, lexer);
			ptr++;
		}
		lexer = lexer->next;
	}
}

void	ft_lexer(t_lexer *list)
{
	//if (!ft_check_quote(list->str))
		//write(1, "Error\n", 6);
	ft_scan(list);
}