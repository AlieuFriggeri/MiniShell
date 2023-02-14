/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:57:05 by kistod            #+#    #+#             */
/*   Updated: 2023/02/14 16:11:32 by afrigger         ###   ########.fr       */
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

	i = 0;
	prompt = ft_strjoin(getenv("USER"), "@minishell-->");
	lexer = malloc(sizeof(t_lexer));
	while(1)
	 {	pipe(fd[0]);
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
			printf("nbpipe is %d\n", nbpipe(&lexer));
			if (nbpipe(&lexer) >= 1)
			{ pipex(&pars, &lexer, envp);
			// int pid = fork();
			// if (pid == 0)
			// {
			// 	dup2(fd[0][1], 1);
			// 	close(fd[0][0]);
			// 	close(fd[0][1]);
			// 	exec_cmd(&pars, &lexer, envp);
			// }
			// int pid2 = fork();
			// if(pid2 == 0)
			// {
			// 	dup2(fd[0][0], 0);
			// 	dup2(fd[1][1], 1); comment
			// 	close(fd[0][0]);
			// 	close(fd[0][1]);
			// 	waitpid(pid, NULL, 0);
			// 	pars = pars->next;
			// 	exec_cmd(&pars, &lexer, envp);
			// }
			// dup2(fd[1][0], 0); comment
			// close(fd[0][0]);
			// close(fd[0][1]);
			// waitpid(pid, NULL, 0);
			// waitpid(pid2, NULL, 0);
			}
			else
			{
				pars->pid = fork();
				if (pars->pid == 0)
				{
					exec_cmd(&pars, &lexer, envp);
				}
				waitpid(pars->pid, NULL, 0);
			}
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


void	pipex(t_parser **pars, t_lexer **lex, char **envp)
{
	t_parser	*tmp;
	int			fd[nbpipe(lex)][2];
	int			i;
	int pid;
	int pid2;

	tmp = *pars;
	i = 0;
	while(i < nbpipe(lex))
	{
		pipe(fd[i]);
		i++;
	}
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[i][1], 1);
		close_fd(fd, nbpipe(lex));
		exec_cmd(&tmp, lex, envp);
	}
	waitpid(pid, NULL, 0);
	while(i < nbpipe(lex))
	{
		pid2 = fork();
		if(pid2 == 0)
		{
			dup2(fd[i][0], 0);
			if (i < nbpipe(lex))
				dup2(fd[i + 1][1], 1);
			close_fd(fd, nbpipe(lex));
			tmp = tmp->next;
			exec_cmd(&tmp, lex, envp);
		}
		//dup2(fd[1][0], 0);
		//close(fd[i][0]);
		if (i + 1 < nbpipe(lex))
			close(fd[i][1]);
		else
			close_fd(fd, nbpipe(lex));
		waitpid(pid2, NULL, 0);
		i++;
		tmp = tmp->next;
	}
}

void	close_fd(int fd[][2], int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i++;
	}
}