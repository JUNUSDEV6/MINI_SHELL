/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:38:45 by clegros           #+#    #+#             */
/*   Updated: 2024/04/04 11:39:29 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "02_pipex/pipex.h"

typedef struct	s_element
{
	char				*content;
	char				*type;
//	t_element			*prev;
//	t_element			*next;
}	t_element;

typedef struct	s_historic
{
	char				*content;
	struct s_historic	*next;
}	t_historic;

/*
enum	e_token
{
	IS_SPACE = ' ',
};
*/

//-------------------------------EXECUTION--------------------------------//
void		command_executer(char **envp, t_element cmd, t_element word);

//--------------------------------LOOPING---------------------------------//
void		minishell_loop(char *line, char **envp);

//---------------------------------LEXER----------------------------------//
void		ft_dispatch(char *line, t_element cmd, t_element word, t_historic *hist);

#endif
