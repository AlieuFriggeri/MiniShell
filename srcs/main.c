/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:57:05 by kistod            #+#    #+#             */
/*   Updated: 2023/02/09 10:08:34 by kistod           ###   ########.fr       */
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
	int fd[2];
	pipe(fd);
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
		pars->pid = fork();
		if (pars->pid == 0)
			exec_cmd(&pars, &lexer, envp);
		waitpid(pars->pid, NULL, 0);
		}
		printf("slt\n");
		free_lex(&lexer);
		printf("slt\n");
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
		//free_pars(&pars);
		//printf("finished lexing and err is\n");
	}
	free(lexer);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
