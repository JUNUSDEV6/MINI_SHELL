/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:44:28 by clegros           #+#    #+#             */
/*   Updated: 2024/05/14 16:58:59 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler(int sign)
{
	if (sign == SIGINT)
	{
		//g_exit_code = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	/*else if (sign == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}*/
}

void	ft_set_input_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_handler);
}
//
//static void	set_input_signals(void)
//{
//	signal(SIGINT, ft_signal_handler);
//	signal(SIGQUIT, SIG_IGN);
//}

//void	ft_signal_handler2(int sign)
//{
//	if (sign == SIGINT)
//		ft_putendl_fd("", 1);
//}
