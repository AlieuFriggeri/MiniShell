/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:48:37 by kistod            #+#    #+#             */
/*   Updated: 2023/02/14 11:20:34 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_parser	*parser(t_lexer **lex)
{
	t_lexer	*tmp;
	t_parser	*parser;
	t_parser	*root;
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
	root = parser;
	while(tmp != NULL)
	{
		parser->fullcmd[i] = tmp->word;
		//ft_printf("parser : %s\n", parser->fullcmd[i]);
		i++;
		if (tmp->token == PIPE)
		{
			parser->fullcmd[i] = NULL;
			parser->next = malloc(sizeof(t_parser) + 1);
			parser = parser->next;
			parser->next = NULL;
			i = 1;
			parser->fullcmd = malloc(sizeof(char *) * countwords(&tmp) + 1);
			if (!parser || !parser->fullcmd)
				return (NULL);
			parser->fullcmd[0] = tmp->next->word;
			parser->envpath = ft_split(getenv("PATH"), ':');
			testpath(&parser);
			//printf("%s\n", parser->fullpath);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	parser->fullcmd[i] = NULL;
	parser->next = NULL;
	return (root);
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
	while(tmp != NULL && tmp->token != PIPE)
	{
		if (tmp->word)
			i++;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return(i);
}

void	tokset(t_parser **parser, int i, t_lexer **lex)
{
	t_parser *tmp;
	t_lexer	*tmpl;

	tmp  = *parser;
	tmpl = *lex;
	if (tmpl->token == LESSLESS)
		tmp->fullcmd[i] = ft_strdup("<<");
	else if (tmpl->token == GREATGREAT)
		tmp->fullcmd[i] = ft_strdup(">>");
	else if (tmpl->token == LESS)
		tmp->fullcmd[i] = ft_strdup("<");
	else if (tmpl->token == GREAT)
		tmp->fullcmd[i] = ft_strdup(">");
	else if (tmpl->token == PIPE)
		tmp->fullcmd[i] = ft_strdup("|");
}
