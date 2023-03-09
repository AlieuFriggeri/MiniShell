/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:57:05 by kistod            #+#    #+#             */
/*   Updated: 2023/03/09 11:36:18 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int g_status = 0;

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
	//int i;

	//i = 0;
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
		//le free ne marche pas vrm sur linux (verifier pourquoi)
		free_lex(&lexer);
		free_pars(&pars);
		//printf("salut je free\n");
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
	int npipe = nbpipe(lex);
	//int stdin = dup(STDIN_FILENO);
	//int stdout = dup(STDOUT_FILENO);

	tmp = *pars;
	i = 0;
	while(i < npipe)
	{
		pipe(fd[i]);
		i++;
	}
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[i][1], 1);
		close_fd(fd, npipe);
		exec_cmd(&tmp, lex, envp);
	}
	waitpid(pid, NULL, 0);
	lexiter(lex);
	t_lexer *tml;
	tml = *lex;
	while(i < npipe)
	{
		pid2 = fork();
		if(pid2 == 0)
		{
			dup2(fd[i][0], 0);
			if (tmp->next != NULL)
				dup2(fd[i + 1][1], 1);
			close_fd(fd, npipe);
			tmp = tmp->next;
			exec_cmd(&tmp, lex, envp);
		}
		//dup2(fd[1][0], 0);
		//close(fd[i][0]);
		if (i + 1 < npipe)
			close(fd[i][1]);
		else
			close_fd(fd, npipe);
		waitpid(pid2, NULL, 0);
		i++;
		tmp = tmp->next;
		lexiter(lex);
		// dup2(stdin, 0);
		// dup2(stdout, 1);
		// close(stdin);
		// close(stdout);
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

void	lexiter(t_lexer **lex)
{
	t_lexer *tml;

	tml = *lex;
	while (tml->token != PIPE && tml->next != NULL)
		tml = tml->next;
	if (tml->token == PIPE)
		tml = tml->next;
	*lex = tml;
}