/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:23:51 by kistod            #+#    #+#             */
/*   Updated: 2023/01/31 10:47:10 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	splitline(char *str, t_lexer **lex)
{
	int i;
	int j;
	t_lexer *tmp;

	tmp  = *lex;
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ' && str[i])
			i++;
		if (tokencheck(str, i, &tmp) != 0)
		{
			if (tmp->token >= 14)
			{
				i += 3;
			}
			else if (tmp->token <= 13 && tmp->token >= 11)
				i += 2;
			j = i;
			while (str[i] == ' ' && str[i])
				i++;
		}
		else if (isquote(str, i) != 0)
		{
			if((i = quotecheck(str, i, tmp)) == 1)
			{
				perror("quote non fermée\n");
				return;
			}
			j = i;
			while (str[i] == ' ' && str[i])
				i++;
		}
		else
		{
			j = i;
			while (str[i] != ' ' && str[i])
				i++;
			tmp->word = ft_substr(str, j, i - j);
			i++;
			while (str[i] == ' ' && str[i])
				i++;
		}
		if (i >= (int)ft_strlen(str))
			break ;
		tmp->next = malloc(sizeof(t_lexer *));
		tmp = tmp->next;
		tmp->next = NULL;
	}
}

int	spaceonly(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int	tokencheck(char *str, int i, t_lexer **lex)
{
	t_lexer *tmp;
	
	tmp = *lex;
	if (str[i] == '<' && str[i + 1] == '<')
		tmp->token = LESSLESS;
	else if (str[i] == '>' && str[i + 1] == '>')
		tmp->token = GREATGREAT;
	else if (str[i] == '<' && str[i + 1] != '<')
		tmp->token = LESS;
	else if (str[i] == '>' && str[i + 1] != '>')
		tmp->token = GREAT;
	else if (str[i] == '|')
		tmp->token = PIPE;
	else
	{
		tmp->token = 0;
		return (0);
	}
	tmp->word = NULL;
	return tmp->token;
}

int	quotecheck(char *str, int index, t_lexer *tmp)
{
	int j;
	int i;

	i = index;
	j = i;
	if (isquote(str, i) == 1)
	{
		i++;
		while (str[i] != '\'' && str[i])
			i++;
		if (i >= (int)ft_strlen(str))
			return (1);
		tmp->word = ft_substr(str, j, i - j + 1);
		i += 1;
	}
	else if (isquote(str, i) == 2)
	{
		i++;
		while (str[i] != '"' && str[i])
			i++;
 		if (i >= (int)ft_strlen(str))
			return (1);
		tmp->word = ft_substr(str, j, i - j + 1);
		i += 1;
	}
	else 
		return (1);
	return i;
}

int	isquote(char *str, int i)
{
	if (str[i] == '\'')
		return 1;
	else if (str[i] == '"')
		return 2;
	else
		return 0;
}
