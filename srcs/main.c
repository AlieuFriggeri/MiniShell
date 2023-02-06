/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:57:05 by kistod            #+#    #+#             */
/*   Updated: 2023/02/06 13:26:02 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *str;
	using_history();
	(void)av;
	(void)ac;
	t_lexer *lexer;
	t_parser *pars;
	int fd[2];
	pipe(fd);
	lexer = malloc(sizeof(t_lexer));
	while(1)
	{
		str = readline("Minishell $");
		if (ft_strncmp("exit", str, 4) == 0)
			exit(1);
		if (ft_strlen(str) > 0)
			add_history(str);
		splitline(str, &lexer);
		expander(&lexer);
		pars = parser(&lexer);
		pars->pid = fork();
		if (pars->pid == 0)
			exec_cmd(&pars, &lexer, envp);
		waitpid(pars->pid, NULL, 0);
		int i = 1;
		while (lexer != NULL)
		{
		if(lexer->word != NULL)
		printf("word %d : %s\n", i, lexer->word);
		if (lexer->token != 0)
		printf("token %d : %d\n", i, lexer->token);
		if (lexer->next == NULL)
			break ;
		lexer = lexer->next;
		i++;
		}
		free(pars);
		//int err = rl_on_new_line();
		printf("finished lexing and err is\n");
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
