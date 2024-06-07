/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:33:23 by clegros           #+#    #+#             */
/*   Updated: 2024/06/01 15:23:28 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_simple_cmds *cmd)
{
	char	*crt_wd;
	char	*new_wd;

	crt_wd = NULL;
	new_wd = NULL;
	crt_wd = getcwd(crt_wd, sizeof(size_t));
	crt_wd = ft_strjoin(crt_wd, "/");
	new_wd = ft_strjoin(crt_wd, cmd->str[1]);
	printf("-crt-%s--\n-new-%s--\n", crt_wd, new_wd);
	chdir(new_wd);

	return (EXIT_SUCCESS);
}
