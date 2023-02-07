/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:17:01 by kistod            #+#    #+#             */
/*   Updated: 2023/02/07 10:49:16 by kistod           ###   ########.fr       */
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
	tmp->outfile = open(tml->word, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (tmp->outfile == -1)
		perror(strerror(ENOENT));
	dup2(tmp->outfile, STDOUT_FILENO);
	close(tmp->outfile);
}

void	append_redirect_out(t_parser **pars, t_lexer **lex)
{
	t_parser	*tmp;
	t_lexer		*tml;
	
	tml = *lex;
	tmp = *pars;
	tml = tml->next;	
	tmp->outfile = open(tml->word, O_APPEND | O_WRONLY | O_CREAT, 0777);
	if (tmp->outfile < 0)
		perror(strerror(ENOENT));
	dup2(tmp->outfile, STDOUT_FILENO);
	close(tmp->outfile);
}

void	heredoc(t_parser **pars, t_lexer **lex)
{
	//t_parser	*tmp;
	t_lexer	*tml;
	char *str;

	tml = *lex;
	tml = tml->next;
	(void)pars;
/* 	tmp->outfile = open(tml->word, O_WRONLY |O_CREAT, 0777);
	if (tmp->outfile < 0)
		perror(strerror(ENOENT));
	dup2(tmp->outfile, STDOUT_FILENO);
	close(tmp->outfile); */
	printf("%s", tml->word);
	while(ft_strncmp(str, tml->word, ft_strlen(tml->word) != 0))
		str = readline(">");
}

void	check_redirect(t_lexer **lex, t_parser **pars)
{
	t_lexer *tml;
	t_parser *tmp;

	tmp = *pars;
	tml = *lex;
	while(tml != NULL)
	{
		if (tml->token == LESS)
			redirect_in(&tmp, &tml);
		else if (tml->token == GREAT)
			redirect_out(&tmp, &tml);
		else if (tml->token == GREATGREAT)
			append_redirect_out(&tmp, &tml);
		else if (tml->token == LESSLESS)
			heredoc(&tmp, &tml);
		if (tml->next == NULL)
			break ;
		tml = tml->next;
	}
}