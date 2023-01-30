/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kistod <kistod@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:47:39 by kistod            #+#    #+#             */
/*   Updated: 2023/01/25 10:12:42 by kistod           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	splitpath(char **envp, t_pipe *pipex)
{
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	pipex->paths = ft_split(*envp + 5, ':');
}

void	testpath(t_pipe *pipex)
{
	int i;

	i = 0;
	while (pipex->paths[i] != NULL)
	{
		pipex->pathok = ft_strjoin(pipex->paths[i], "/");
		pipex->pathok = ft_strjoin(pipex->pathok, pipex->cmd1);
		if (access(pipex->pathok, F_OK | X_OK) != 0)
		{
			free(pipex->pathok);
			pipex->pathok = NULL;
		}
		else
			break ;
		i++;
	}
}

void	set_args(t_pipe *pipex, char *args)
{
	pipex->cmd1_args = ft_split(args, ' ');
	pipex->cmd1 = pipex->cmd1_args[0];
}

void	errcheck(t_pipe *pipex)
{
	if (WIFEXITED(pipex->wstatus))
		pipex->statuscode = WEXITSTATUS(pipex->wstatus);
	if (pipex->statuscode != 0)
	{
		perror(strerror(pipex->statuscode));
		exit(pipex->statuscode);
	}
}