/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:01:05 by yohanafi          #+#    #+#             */
/*   Updated: 2024/05/15 15:45:12 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check_hrdoc(char **args)
{
	 int i;
    int j;
	int rlt;
	
	i = 0;
	j = 0;
	rlt = 0;
    while (args[i]) 
	{
        j = 0;
        while (args[i][j]) 
		{
            if (!strncmp(args[i] + j, "<<", 2)) 
			{
                printf("heredoc: %s\n", args[i]);
                rlt = 1;
            }
            j++;
        }
        i++;
    }
    return (rlt);
}
