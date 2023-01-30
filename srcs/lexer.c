/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:23:51 by kistod            #+#    #+#             */
/*   Updated: 2023/01/30 09:35:00 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	splitline(char *str, t_lexer **lex)
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
		cmd = malloc(1024);
		if (tokencheck(str, i, &tmp) == 1)
			i++;
		else if (isquote(str, i) == 1)
		{
			i++;
			while (isquote(str, i) != 1)
			{
				cmd[j] = str[i];
				i++;
				j++;
				tmp->quote = 1;
			}
		}
		else if (isquote(str, i) == 2)
		{
			i++;
			while (isquote(str, i) != 1)
			{
				cmd[j] = str[i];
				i++;
				j++;
				tmp->dquote = 1;
			}
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
		printf("word is %s\n", cmd);
		if (tmp->token == 0)
		tmp->word = ft_strdup(cmd);
		printf("word duped is %s\n", tmp->word);
		tmp->next = malloc(sizeof(t_lexer *));
		tmp = tmp->next;
		tmp->next = NULL;
		free(cmd);
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
	tmp->word = 0;
	return 1;
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
