/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:28 by clegros           #+#    #+#             */
/*   Updated: 2024/04/10 13:51:34 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_lexero(char **args, t_lexer *list)
{
	int		i;
	t_lexer	*elem;
	t_lexer	*head;

	i = 0;
	head = list;
	while (args[i] != NULL)
	{
		
		elem = ft_lstnew(args[i]);
		if (list->str == NULL)
		{
			list = elem;
			head = list;
		}
		else
		{
			if (list->next)
				list = list->next;
			ft_lstadd_back(&list, elem);
		}
		if (list != NULL)
		{
//			printf("3--%s--\n", list->str);
		}
		i++;
	}
	return (head);
}

/*t_lexer	ft_dispatch(char *line, t_lexer elem)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		//ft_line_valid(line);
		if (ft_strncmp(&line[i], "cat", 3) == 0)
		{
			elem.cmd = ft_strdup("/bin/cat");
			i += 3;
			while (line[i] == ' ')
				i++;
			while (line[i + j] != ' ' && line[i + j] != '\0')
				j++;
			elem.word = strndup(&line[i], j);
			return (elem);
		}
		i++;
	}
	return (elem);
}*/
