/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:17:01 by kistod            #+#    #+#             */
/*   Updated: 2023/02/03 10:25:36 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	redirect_in(t_parser **pars, t_lexer **lex)
{
	t_parser	*tmp;
	t_lexer		*tml;
	
	tml = *lex;
	tmp = *pars;
	tml = tml->next;
	tmp->infile = open(tml->word, O_RDONLY);
	if (tmp->infile == -1)
		perror(strerror(ENOENT));
	dup2(tmp->infile, STDIN_FILENO);
	close(tmp->infile);
}

void	redirect_out(t_parser **pars, t_lexer **lex)
{
	t_parser	*tmp;
	t_lexer		*tml;
	
	tml = *lex;
	tmp = *pars;
	tml = tml->next;
	tmp->outfile = open(tml->word, O_WRONLY | O_CREAT, 0777);
	if (tmp->outfile == -1)
		perror(strerror(ENOENT));
	dup2(tmp->outfile, STDOUT_FILENO);
	close(tmp->outfile);
}