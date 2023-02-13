/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:43:09 by kistod            #+#    #+#             */
/*   Updated: 2023/02/13 14:00:24 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_pars(t_parser **pars)
{
	t_parser	*tmp;
	t_parser	*tmp2;

	tmp = *pars;
	if (!tmp->envpath || !tmp->fullcmd ||!tmp->fullpath || !tmp)
		return;
	if (tmp->next != NULL)
	{
		tmp = tmp->next;
		while (tmp != NULL)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2->envpath);
			free(tmp2->fullcmd);
			free(tmp2->fullpath);
			tmp2->envpath = NULL;
			tmp2->fullcmd = NULL;
			tmp2->fullpath = NULL;
		}
		tmp = *pars;
		free(tmp->envpath);
		free(tmp->fullcmd);
		free(tmp->fullpath);
		tmp->envpath = NULL;
		tmp->fullcmd = NULL;
		tmp->fullpath = NULL;
		tmp->next = NULL;
	}
	else
	{
		// if (tmp->envpath)
		// 	free_array(tmp->envpath);
		tmp->envpath = NULL;
		tmp->fullcmd = NULL;
		free(tmp->fullpath);
		tmp->fullpath = NULL;
		tmp->next = NULL;
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
		if (tmp->word)
			free(tmp->word);
		tmp->word = NULL;
		tmp->next = NULL;
	}
}

void	free_array(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		printf("%d\n", i);
		i++;
	}
	str = NULL;
}