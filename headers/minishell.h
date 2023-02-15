/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:56:59 by kistod            #+#    #+#             */
/*   Updated: 2023/02/15 09:59:07 by kistod           ###   ########.fr       */
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

#define EOFF 10
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
	int				outfile;
	int				infile;
	int				nword;
}	t_lexer;

typedef	struct s_parser
{
	char	**fullcmd;
	char	*fullpath;
	char	**envpath;
	int		infile;
	int		outfile;
	int		redirect;
	int		pid;
	struct s_parser	*next;
}	t_parser;

//main.c
void	pipex(t_parser **pars, t_lexer **lex, char **envp);
void	close_fd(int fd[][2], int nb);

//lexer.c
int			isquote(char *str, int i);
int			tokencheck(char *str, int i, t_lexer **lex);
void		splitline(char *str, t_lexer **lex);
int			quotecheck(char *str, int index, t_lexer *tmp);
int			spaceonly(char *str);

//expander.c
void		expander(t_lexer **lex);

//parser.c
t_parser	*parser(t_lexer **lex);
void		testpath(t_parser **parser);
int			countwords(t_lexer **lex);
int			nbpipe(t_lexer **lex);
void		tokset(t_parser **parser, int i, t_lexer **lex);

//redirect.c
void		redirect_in(t_parser **pars, t_lexer **lex);
void		redirect_out(t_parser **pars, t_lexer **lex);
void	check_redirect(t_lexer **lex, t_parser **pars);
void	append_redirect_out(t_parser **pars, t_lexer **lex);
void	heredoc(t_parser **pars, t_lexer **lex);

//exec.c
void	exec_cmd(t_parser **pars, t_lexer **lex, char **envp);

//free.c
void	free_lex(t_lexer **lex);
void	free_pars(t_parser **pars);
void	free_array(char **str);


#endif