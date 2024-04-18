/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:40:14 by yohanafi          #+#    #+#             */
/*   Updated: 2024/04/18 14:24:10 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	ft_check_where_quotes(char *str)
{
	int	i = 0;
	int	j = 0;

	while(str[i])
	{
		if (str[i] == DOUBLE_QUOTE)
		{
			j = 0;
			while(str[i + j] != DOUBLE_QUOTE)
			{
				
				j++;
			}
		}
	}

}

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

    // Si les guillemets doubles sont ouverts ou les guillemets simples sont ouverts, alors ils ne sont pas bien appariés
    double_flag = !in_double_quotes;
    single_flag = !in_single_quotes;

    // Retourne true si les guillemets doubles et simples sont correctement appariés
    return (double_flag && single_flag);
	//int	i = 0;
	//bool	D_Q_flag = true;
//
	//while (str[i])
	//{
	//	if (str[i] == DOUBLE_QUOTE && flag == true)
	//		flag = false;
	//	else if (str[i] == DOUBLE_QUOTE && flag == false)
	//		flag = true;
	//	i++;
	//}
	//if (idq % 2 == 0 && iq % 2 == 0)
	//	return (true);
	//else
	//	ft_check_where_quotes(str);
	//return (flag);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
}

bool	ft_lexer_token(char c)
{
	if (c == QUOTE || c == DOUBLE_QUOTE)
		return (true);
	if (c == PIPE_LINE)
		return (true);
	if (c == REDIR_IN || c == REDIR_OUT)
		return (true);
	return (false);
}

void	ft_stock_token(char c, t_lexer *lexer)
{
	lexer->chr = c;
	printf("%c\n", lexer->chr);
	lexer = lexer->next;
}

void	ft_scan(char *str, t_lexer *lexer)
{
	int i = 0;

	while (str[i])
	{
		if (ft_lexer_token(str[i]) == true)
			ft_stock_token(str[i], lexer);
		i++;
	}
}

void	ft_lexer(char *str)
{
	t_lexer	*lexer = malloc(sizeof(t_lexer));
	ft_scan(str, lexer);
}

int	main(void)
{
	char	*str;
	int		i = 0;
	str = "ls -la | \"gr'ep\" <a> \"| t'r\" 'a-z' 'A-Z'";

	if (!ft_check_quote(str))
		write(1, "Error\n", 6);
	//ft_lexer(str);
}