/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:23:35 by clegros           #+#    #+#             */
/*   Updated: 2024/06/01 15:24:08 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	output(int i, char **str, int fd)
{
	while (str[i])
	{
		ft_putstr_fd("\033[4m\033[92mbefore pimped echo\033[0m\n", STDOUT_FILENO);
		ft_putstr_fd(str[i++], fd);
		if (str[i])
			ft_putchar_fd(' ', fd);
	}
}

int	ft_echo(t_simple_cmds *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->str[i])
	{
		j = 0;
		while (cmd->str[i][j] != '\0')
			j++;
		i++;
	}
	output(1, cmd->str, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putstr_fd("\033[4m\033[92mpersonal echo\033[0m\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
