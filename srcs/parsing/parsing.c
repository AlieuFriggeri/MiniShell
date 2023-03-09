/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:42:27 by hradoux           #+#    #+#             */
/*   Updated: 2023/03/09 12:01:22 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SPACE 32
#define QUOTE 39
#define DQUOTE 34
#define BSLASH 92


int	ft_word_count_parse(char const *s, char c)
{
	int	quote;
	int	word_count;

	quote = 0;
	word_count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			word_count++;
		while ((*s && *s != c) || (*s && quote))
		{
			if (*s == QUOTE || (*s == DQUOTE && *(s - 1) != BSLASH))
			{
				if (!quote || quote == *s)
					quote = (quote - *s) * -1;
			}
			s++;
		}
	}
	return (word_count);
}

int	string_size_parse(char const *s, char c)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while ((*s && *s != c) || (*s && quote))
	{
		if (*s == BSLASH && *(s + 1) == DQUOTE)
			s++;
		if (*s == QUOTE || (*s == DQUOTE && *(s - 1) != BSLASH))
		{
			if (!quote || quote == *s)
				quote = (quote - *s) * -1;
			if (*s != quote && quote)
				i++;
		}
		else
			i++;
		s++;
	}
	return (i);
}

void	get_string_parse(char **tmp, char const *s, char c)
{
	int	quote;

	quote = 0;
	while ((*s && *s != c) || (*s && quote))
	{
		if (*s == BSLASH && *(s + 1) == DQUOTE)
			s++;
		if (*s == QUOTE || (*s == 34 && *(s - 1) != BSLASH))
		{
			if (!quote || quote == *s)
				quote = (quote - *s) * -1;
			if (*s != quote && quote)
				*((*tmp)++) = *s;
		}
		else
			*((*tmp)++) = *s;
		s++;
	}
}

char	*dup_string_parse(char const *s, char c)
{
	char	*tmp;
	char	*tmp_start;

	tmp = ft_calloc(string_size_parse(s, SPACE) + 1, sizeof(char));
	if (!tmp)
		return (0);
	tmp_start = tmp;
	get_string_parse(&tmp, s, c);
	return (tmp_start);
}

char	**ft_split_parse(char const *s, char c)
{
	int		word_count;
	char	**tmp;
	int		quote;

	word_count = ft_word_count_parse(s, c);
	tmp = ft_calloc(word_count + 1, sizeof(char *));
	if (!tmp)
		return (0);
	quote = 0;
	while (*s)
	{
		while (*s && *s == SPACE)
			s++;
		if (*s)
			*tmp++ = dup_string_parse(s, c);
		while ((*s && *s != c) || (*s && quote))
		{
			if (*s == QUOTE || (*s == DQUOTE && *(s - 1) != 92))
			{
				if (!quote || quote == *s)
					quote = (quote - *s) * -1;
			}
			s++;
		}
	}
	tmp -= word_count;
	return (tmp);
}
