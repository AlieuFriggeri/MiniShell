/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hradoux <hradoux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:00:05 by hradoux           #+#    #+#             */
/*   Updated: 2023/02/22 16:00:08 by hradoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_in_env(char const *s, char **env)
{
	int	i;

	while (*env)
	{
		i = 0;
		while (s[i] && (*env)[i] == s[i])
			i++;
		if ((*env)[i] == '=' && (s[i] == 0 || s[i] == ' ' || s[i] == '\"' || s[i] == '\''))
			return (&(*env)[i + 1]);
		env++;
	}
	return (NULL);
}

size_t	var_length(char const *s, char **env)
{
	char	*tmp;

	tmp = var_in_env(s, env);
	if (!tmp)
		return (0);
	return (ft_strlen(tmp));
}

size_t	var_swap_size(char const *s, char **env)
{
	int		quote;
	size_t	i;

	i = 0;
	quote = 0;
	while (*s)
	{
		if (*s == 92 && *(s + 1) == 34)
			s++;
		//	quand cest dans '' on ecrit tel quel balec
		if (*s == '$' && quote == 39)
			i++;
			//	quand cest dans ""
		else if (*s == '$' && quote == 34)
		{
			// " ou ' just apres $ alors que dans ""
			if (*(s + 1) == 34 || *(s + 1) == 39)
				i++;
				// cas ?
			else if (*(s + 1) == '?')
			{
				i += ft_strlen(ft_itoa(g_status));
				s++;
			}
				// le reste
			else
			{
				i += var_length(s + 1, env);
				//avancer jusqu'a fin def de la variable
				while (*(s + 1) && *(s + 1) != 34 && *(s + 1) != 39 && *(s + 1) != 32)
					s++;
			}
		}
			//quand cest dans rien
		else if (*s == '$' && !quote)
		{
			if (*(s + 1) == 34 || *(s + 1) == 39)
				;
			else if (*(s + 1) == '?')
			{
				i += ft_strlen(ft_itoa(g_status));
				s++;
			}
			else
			{
				i += (var_length(s + 1, env));
				//avancer jusqu'a fin def de la variable
				while (*(s + 1) && *(s + 1) != 34 && *(s + 1) != 39 && *(s + 1) != 32)
					s++;
			}
		}
		else if (*s == 39 || *s == 34)
		{
			if (!quote || quote == *s)
				quote = (quote - *s) * -1;
			if (*s != quote && quote)
				i++;
		}
		else
			i++;
		s++;
	}
	return (i);
}

char	*swap_var(char const *s, char **env)
{
	int		quote;
	char	*var;
	char	*tmp;
	char	*tmp_start;

	quote = 0;
	tmp = ft_calloc(var_swap_size(s, env) + 1, sizeof(char));
	if (!tmp)
		return (0);
	tmp_start = tmp;
	while (*s)
	{
		//	quand cest dans '' on ecrit tel quel balec
		if (*s == '$' && quote == 39)
			*(tmp++) = *s;
			//	quand cest dans ""
		else if (*s == '$' && quote == 34)
		{
			// " ou ' just apres $ alors que dans ""
			if (*(s + 1) == 34 || *(s + 1) == 39)
				*(tmp++) = *s;
			// cas ?
			else if (*(s + 1) == '?')
			{
				var = ft_itoa(g_status);
				while (var && *var)
					*(tmp++) = *(var++);
				s++;
			}
			// le reste
			else
			{
				var = var_in_env(s + 1, env);
				while (var && *var)
					*(tmp++) = *(var++);
				while (*(s + 1) && *(s + 1) != 34 && *(s + 1) != 39 && *(s + 1) != 32)
					s++;
			}
		}
		//quand cest dans rien
		else if (*s == '$' && !quote)
		{
			if (*(s + 1) == 34 || *(s + 1) == 39)
				;
			else if (*(s + 1) == '?')
			{
				var = ft_itoa(g_status);
				while (var && *var)
					*(tmp++) = *(var++);
				s++;
			}
			else
			{
				var = var_in_env(s + 1, env);
				while (var && *var)
					*(tmp++) = *(var++);
				while (*(s + 1) && *(s + 1) != 34 && *(s + 1) != 39 && *(s + 1) != 32)
					s++;
			}
		}
		else if (*s == 39 || *s == 34)
		{
			if (!quote || quote == *s)
				quote = (quote - *s) * -1;
			if (*s != quote && quote)
				*(tmp++) = *s;
		}
		else
			*(tmp++) = *s;
		s++;
	}
	return (tmp_start);
}