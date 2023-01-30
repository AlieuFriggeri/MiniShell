/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:23:51 by kistod            #+#    #+#             */
/*   Updated: 2023/01/30 15:57:58 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* void	splitline(char *str, t_lexer **lex)
{
	int i;
	char *cmd;
	int j;
	t_lexer *tmp;

	i = 0;
	tmp = *lex;
	while (str[i])
	{
		j = 0;
		cmd = malloc(5000);
		while (str[i] == ' ')
			i++;
		if (tokencheck(str, i, &tmp) == 14 || tokencheck(str, i, &tmp) == 15)
			i += 2;
		else if(tokencheck(str, i, &tmp) != 0)
			i++;
		else if (isquote(str, i) == 1)
		{
			i++;
			while (isquote(str, i) != 1 && str[i])
			{
				cmd[j] = str[i];
				i++;
				j++;	
			}
			tmp->quote = 1;
			i++;
		}
		else if (isquote(str, i) == 2)
		{
			i++;
			while (isquote(str, i) != 2 && str[i])
			{
				cmd[j] = str[i];
				i++;
				j++;
			}
			tmp->dquote = 1;
			i++;
		}
		else
		{
			while (str[i] != ' ' && str[i] != '\t' && str[i])
			{
				cmd[j] = str[i];
				j++;
				i++;
			}
			i++;
		}
		cmd[j] = '\0';
		ft_printf("word is %s\n", cmd);
		if (tmp->token == 0)
		{
			tmp->word = ft_strdup(cmd);
			printf("word duped is %s\n", tmp->word);
		}
		tmp->next = malloc(sizeof(t_lexer *));
		tmp = tmp->next;
		printf("bruh\n");
		tmp->next = NULL;
		free(cmd);
	}
} */

void	splitline2(char *str, t_lexer **lex)
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
			if (tokencheck(str, i, &tmp) >= 14)
				i += 3;
			else
				i += 2;
			j = i;
		}
		else if (isquote(str, i) != 0)
		{
			if(quotecheck(str, &i, &tmp) != 0)
			{
				perror("quote non fermée\n");
				exit(1);
			}
		}
		else
		{
			while (str[i] != ' ' && str[i])
				i++;
			tmp->word = ft_substr(str, j, i - j);
			i++;
			j = i;
		}
		tmp->next = malloc(sizeof(t_lexer *));
		tmp = tmp->next;
		tmp->next = NULL;
	}
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

int	quotecheck(char *str, int *i, t_lexer **lexer)
{
	int j;
	t_lexer	*tmp;

	j = *i;
	tmp = *lexer;
	if (isquote(str, *i) == 1)
	{
		while (str[*i] != '\'' && str[*i])
			i++;
		if (*i >= (int)ft_strlen(str))
			return (1);
		tmp->word = ft_substr(str, j, j - *i);
		*i += 1;
	}
	else if (isquote(str, *i) == 2)
	{
		while (str[*i] != '"' && str[*i])
			i++;
		if (*i >= (int)ft_strlen(str))
			return (1);
		tmp->word = ft_substr(str, j, j - *i);
		*i += 1;
	}
	else
		return (1);
	return 0;
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
