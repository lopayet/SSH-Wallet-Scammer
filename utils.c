/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:05:37 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/15 14:36:08 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wshell.h"

char	*rl_get(char *prompt)
{
	char	*input;
	char	*trimmed;

	input = readline(prompt);
	if (input == NULL)
		return (NULL);
	trimmed = strtrim(input, " \t");
	if (!trimmed)
		return (NULL);
	free(input);
	return (trimmed);
}

static void	new_prompt(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

char	*strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1)
		return (0);
	start = 0;
	while (s1[start] && strchr(set, s1[start]))
		start ++;
	end = strlen(s1);
	while ((end > start) && strchr(set, s1[end - 1]))
		end--;
	i = 0;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (0);
	while (start < end)
	{
		str[i++] = s1[start];
		start ++;
	}
	str[i] = 0;
	return (str);
}

void	run_signal(int nb)
{
	if (nb == 1)
	{
		signal(SIGINT, &new_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
}
