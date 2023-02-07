/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:32:39 by kistod            #+#    #+#             */
/*   Updated: 2023/02/07 10:41:43 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	exec_cmd(t_parser **pars, t_lexer **lex, char **envp)
{
	t_parser	*tmp;
	int			error;

	tmp = *pars;
	check_redirect(lex, pars);
	error = execve(tmp->fullpath, tmp->fullcmd + 1, envp);
	if (error != 0)
	{
		printf("%s : command not found\n", tmp->fullcmd[0]);
		exit (1);
	}
}
