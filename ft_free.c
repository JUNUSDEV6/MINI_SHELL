/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:21:52 by clegros           #+#    #+#             */
/*   Updated: 2024/04/10 09:21:54 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *line, t_lexer elem)
{
	free(line);
	(void)elem;
//	free(elem.cmd);
//	free(elem.word);
}