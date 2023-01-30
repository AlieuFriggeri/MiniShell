/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:57:05 by kistod            #+#    #+#             */
/*   Updated: 2023/01/30 09:36:46 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)envp;
	char *str;
	using_history();
	(void)av;
	(void)ac;
	t_lexer *lexer;
	lexer = malloc(sizeof(t_lexer *));
	while(1)
	{
		str = readline("Minishell - -> ");
		if (ft_strncmp("exit", str, 4) == 0)
			exit(1);
		if (ft_strlen(str) > 0)
			add_history(str);
		splitline(str, &lexer);
		printf("word %s\n", lexer->word);
		printf("token %d\n", lexer->token);
		lexer = lexer->next;
		printf("word %s\n", lexer->word);
		printf("token %d\n", lexer->token);
		free(str);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
