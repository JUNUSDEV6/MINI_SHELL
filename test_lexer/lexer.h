/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:25:48 by yohanafi          #+#    #+#             */
/*   Updated: 2024/04/17 17:41:29 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

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

typedef struct s_lexer
{
	char	*str;
	char	chr;
	int		leng;
	enum	e_token;
	enum	e_state;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}			t_lexer;
