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

static void	ctrl_c_handle(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	is_str_valid_float(char *str);
int	amount_check(t_data *data, char *str)
{
	float	amount;

	if (!is_str_valid_float(str))
	{
		printf("Error: Invalid number format.\n");
		return (1);
	}
	amount = atof(str);
	if (amount > data->balance)
	{
		printf("Error: Insufficient funds.\n");
		return (1);
	}
	if (amount < data->scam_amount)
	{
		printf("Error: This account doesn't allow withdrawals under %s.\n", SCAM_AMOUNT);
		return (1);
	}
	return (0);
}

int		char_is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int		is_str_valid_float(char *str)
{
	int	i;
	int	period_count;

	i = 0;
	if (!str[i] || !char_is_num(str[i]))
		return (0);
	period_count = 0;
	while (str[i])
	{
		if (!(str[i] == '.' || char_is_num(str[i])))
			return (0);
		if (str[i] == '.')
			period_count++;
		if (str[i] == '.' && !str[i + 1])
			return (0);
		i++;
	}
	if (period_count > 1)
		return (0);
	return (1);
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

int		is_withdrawing(t_data *data)
{
	return (data->program_mode == MODE_WITHDRAW_AMOUNT
	|| data->program_mode == MODE_WITHDRAW_ADDR
	|| data->program_mode == MODE_WITHDRAW_ADDR_2
	|| data->program_mode == MODE_WITHDRAW_CONFIRM);
}

void	run_signal(int nb)
{
	if (nb == 1)
	{
		signal(SIGINT, &ctrl_c_handle);
		signal(SIGQUIT, SIG_IGN);
	}
}
