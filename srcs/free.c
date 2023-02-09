/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:43:09 by kistod            #+#    #+#             */
/*   Updated: 2023/02/09 10:10:51 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_pars(t_parser **pars)
{
	t_parser	*tmp;
	t_parser	*tmp2;

	tmp = *pars;
	while (tmp != NULL)
	{
		if (!tmp)
			break ;
		tmp2 = tmp;
		free(tmp2->fullcmd);
		free(tmp2->fullpath);
		free(tmp2);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}

void	free_lex(t_lexer **lex)
{
	t_lexer *tmp;
	t_lexer *tmp2;

	tmp = *lex;
	if (!tmp || !tmp->word)
		return;
	if (tmp->next != NULL)
	{
		tmp = tmp->next;
		while (tmp != NULL)
		{
			tmp2 = tmp;
			if (tmp->next == NULL)
				break ; 
			tmp = tmp->next;
			if (tmp2->word)
				free(tmp2->word);
			else if (tmp2->token != 0)
				tmp2->token = 0;
		}
		if (tmp->word)
			free(tmp->word);
		free(tmp);
		tmp = *lex;
		free(tmp->word);
		tmp->word = NULL;
		tmp->next = NULL;
	}
	else
	{
		free(tmp->word);
		tmp->word = NULL;
		tmp->next = NULL;
	}
}