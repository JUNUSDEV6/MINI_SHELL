/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:24:45 by clegros           #+#    #+#             */
/*   Updated: 2024/05/29 10:24:48 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(const char *var_name)
{
	return (getenv(var_name));
}

int	count_occurrences(const char *str, const char *old_substr)
{
	int			count;
	int			oldlen;
	const char	*temp;

	count = 0;
	oldlen = strlen(old_substr);
	temp = str;
	while (1)
	{
		temp = strstr(temp, old_substr);
		if (!temp)
			break ;
		count++;
		temp += oldlen;
	}
	return (count);
}

char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}

char	*allocate_result(char *str, char *old_substr, char *new_substr)
{
	int		count;
	int		newlen;
	int		oldlen;
	char	*result;

	count = count_occurrences(str, old_substr);
	newlen = strlen(new_substr);
	oldlen = strlen(old_substr);
	result = (char *)malloc(strlen(str) + count * (newlen - oldlen) + 1);
	if (!result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (result);
}

char	*replace_substr(char *str, char *old_substr, char *new_substr)
{
	char	*result;
	int		i;
	int		oldlen;
	int		newlen;

	result = allocate_result(str, old_substr, new_substr);
	i = 0;
	oldlen = strlen(old_substr);
	newlen = strlen(new_substr);
	while (*str)
	{
		if (strstr(str, old_substr) == str)
		{
			strcpy(&result[i], new_substr);
			i += newlen;
			str += oldlen;
		}
		else
			result[i++] = *str++;
	}
	result[i] = '\0';
	return (result);
}
