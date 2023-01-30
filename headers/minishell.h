/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:56:59 by kistod            #+#    #+#             */
/*   Updated: 2023/01/30 08:37:43 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

#define PIPE 11
#define LESS 12
#define GREAT 13
#define LESSLESS 14
#define GREATGREAT 15

typedef	struct s_lexer
{
	struct s_lexer			*next;
	int				token;
	char			*word;
	int				quote;
	int				dquote;
}	t_lexer;

//lexer.c
int	isquote(char *str, int i);
int	tokencheck(char *str, int i, t_lexer **lex);
void	splitline(char *str, t_lexer **lex);

#endif