/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:48:37 by kistod            #+#    #+#             */
/*   Updated: 2023/02/01 10:39:56 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_parser	*parser(t_lexer **lex)
{
	t_lexer	*tmp;
	t_parser	*parser;
	int i;

	tmp = *lex;
	i = 1;
	parser = malloc(sizeof(t_parser) + 1);
	parser->fullcmd = malloc((sizeof(char *) * countwords(lex)) + 1);
	if (!parser || !parser->fullcmd)
		return (NULL);
	parser->envpath = ft_split(getenv("PATH"), ':');
	parser->fullcmd[0] = tmp->word;
	testpath(&parser);
	while(tmp->token != PIPE && tmp != NULL)
	{
		parser->fullcmd[i] = tmp->word;
		ft_printf("parser : %s\n", parser->fullcmd[i]);
		i++;
		if (tmp->next == NULL || tmp->next->token != 0)
			break ;
		tmp = tmp->next;
	}
	parser->fullcmd[i] = NULL;
	return parser;
}

void	testpath(t_parser **parser)
{
	int i;
	t_parser	*tmp;

	i = 0;
	tmp = *parser;
	while (tmp->envpath[i] != NULL)
	{
		tmp->fullpath = ft_strjoin(tmp->envpath[i],  "/");
		tmp->fullpath = ft_strjoin(tmp->fullpath, tmp->fullcmd[0]);
		if (access(tmp->fullpath, F_OK | X_OK) != 0)
		{
			free(tmp->fullpath);
			tmp->fullpath = NULL;
		}
		else
			break ;
		i++;
	}
}

int	countwords(t_lexer **lex)
{
	t_lexer *tmp;
	int i;

	i = 0;
	tmp = * lex;
	while(tmp != NULL)
	{
		if (tmp->word)
			i++;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return(i);
}