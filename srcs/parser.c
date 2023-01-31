/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:48:37 by kistod            #+#    #+#             */
/*   Updated: 2023/01/31 14:20:43 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_parser	*parser(t_lexer **lex)
{
	t_lexer	*tmp;
	t_parser	*parser;
	int i;

	tmp = *lex;
	i = 0;
	parser = malloc(sizeof(t_parser *));
	parser->envpath = ft_split(getenv("PATH"), ':');
	while(tmp->token != PIPE && tmp != NULL)
	{
		parser->fullcmd[i] = tmp->word;
		i++;
		tmp = tmp->next;
	}
	return parser;
}

void	testpath(t_parser **parser)
{
	int i;
	t_parser	*tmp;

	i = 0;
	tmp = *parser;
	while (tmp->envpath != NULL)
	{
		tmp->fullpath = ft_strjoin(tmp->envpath[i], "/");
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