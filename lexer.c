/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:31:33 by clegros           #+#    #+#             */
/*   Updated: 2024/04/07 11:31:35 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_historic(t_historic *hist)
{
	printf("--  %s\n", hist->content);
	return ;
}

void	ft_dispatch(char *line, t_element cmd, t_element word, t_historic *hist)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while(line[i] != '\0')
	{
		if (ft_strncmp(&line[i], "cat", 3) == 0)
		{
			strncpy(cmd.content, "cat", 4);
			cmd.type = "built";
			i += 3;
		}
		else if (ft_strncmp(line, "history", 7) == 0)
		{
			ft_historic(hist);
			return ;
		}
		if (line[i] == ' ')
			i++;
		while (line[i + j] != ' ' && line[i + j] != '\0')
			j++;
		strncpy(word.content, "a.txt", 5);
		word.content[j] = '\0';
		word.type = "word";
		i += j;
	}
	return ;
}
