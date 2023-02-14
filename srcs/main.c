/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:57:05 by kistod            #+#    #+#             */
/*   Updated: 2023/02/14 11:20:08 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *str;
	char *prompt;
	using_history();
	(void)av;
	(void)ac;
	t_lexer *lexer;
	t_parser *pars;
	int fd[3][2];
	int i;
	pipe(fd[0]);
	pipe(fd[1]);
	pipe(fd[2]);
	i = 0;
	prompt = ft_strjoin(getenv("USER"), "@minishell-->");
	lexer = malloc(sizeof(t_lexer));
	while(1)
	{
		str = readline(prompt);
		if (ft_strncmp("exit", str, 4) == 0)
			exit(1);
		if (ft_strlen(str) > 0)
			add_history(str);
		if (ft_strncmp(str, "", 2) != 0)
		{
			splitline(str, &lexer);
			expander(&lexer);
			pars = parser(&lexer);
			if (pars->next != NULL)
				printf("pars.next non null\n");
			int pid = fork();
			if (pid == 0)
			{
				exec_cmd(&pars, &lexer, envp);
			}
			int pid2 = fork();
			if(pid2 == 0)
			{
				pars = pars->next;
				exec_cmd(&pars, &lexer, envp);
			}
			waitpid(pid, NULL, 0);
			waitpid(pid2, NULL, 0);
		}	
		free_lex(&lexer);
		free_pars(&pars);
/*  		int i = 1;
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
		} */
		//printf("finished lexing and err is\n");
	}
	clear_history();
	free(pars);
	free(lexer);
	exit(EXIT_SUCCESS);
}
