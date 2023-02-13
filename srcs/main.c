/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:57:05 by kistod            #+#    #+#             */
/*   Updated: 2023/02/13 16:14:31 by afrigger         ###   ########.fr       */
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
	//int fd[2][2];
	int i;

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
			pars->pid = fork();
			if (pars->pid == 0)
				exec_cmd(&pars, &lexer, envp);
			else
				waitpid(pars->pid, NULL, 0);
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
