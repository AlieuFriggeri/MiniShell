/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:09:31 by kistod            #+#    #+#             */
/*   Updated: 2023/02/13 12:27:57 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	expander(t_lexer **lex)
{
	t_lexer *tmp;

	tmp = *lex;
	while (tmp != NULL)
	{
		if (tmp->word != NULL && (tmp->word[0] == '$' || tmp->word[0] == '~'))
		{
			if (tmp->word[0] == '~')
			{
				tmp->word = ft_strdup(getenv("HOME"));
			}
			else if (getenv(ft_substr(tmp->word, 1, ft_strlen(tmp->word))) != NULL)
			{
				tmp->word = ft_strdup(getenv(ft_substr(tmp->word, 1, ft_strlen(tmp->word))));
				
			}
			else
			{
				free(tmp->word);
				tmp->word = ft_strdup("");
			}
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}