/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:38:45 by clegros           #+#    #+#             */
/*   Updated: 2024/04/11 11:34:40 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include "ft_pipex/pipex.h"

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct	s_lexer
{
	char				*str;
	char				chr;
	int					i;
//	enum				e_token;
//	enum				e_state;
	struct s_lexer		*prev;
	struct s_lexer		*next;
}	t_lexer;



//void		rl_replace_line(const char *text, int clear_undo);
//-------------------------------EXECUTION--------------------------------//
void		command_executer(char **envp, t_lexer elem);

//--------------------------------LOOPING---------------------------------//
void		minishell_loop(char *line, char **envp);

//--------------------------------SIGNALS---------------------------------//
void		ft_signal_handler(int sign);
void		ft_set_input_signals(void);
//void		ft_signal_handler2(int sign);

//---------------------------------LEXER----------------------------------//
t_lexer		*ft_lexero(char **args, t_lexer *list);
//t_lexer		ft_dispatch(char *line, t_lexer elem);
void		ft_lexer(t_lexer *list);
bool	ft_check_quote(char *str);

//----------------------------------FREE----------------------------------//
void		ft_free(char *line, t_lexer elem);

void		ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer		*ft_lstlast(t_lexer *lst);
t_lexer		*ft_lstnew(void *content);

//--------------------------------STR_UTILS--------------------------------//

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strtrim(char const *s1, char set);
char	*ft_strchr(char *s, int c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);


#endif
