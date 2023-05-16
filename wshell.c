
#include "wshell.h"

char	g_color_white[32];
char	g_color_red[32];
char	g_color_green[32];
char	g_color_bright_green[32];
char	g_color_bright_red[32];
char	g_color_gray[32];

void	wshell(t_data *data);
char	*get_prompt(t_data *data);
t_data	init_data(char **envp, char **argv);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
		return (1);
	data = init_data(envp, argv);
	wshell(&data);
	free_var_list(&data.env_var_list);
	rl_clear_history();
	return (0);
}

void	wshell(t_data *data)
{
	char		*input;
	char		*prompt;

	run_signal(1);
	while (1)
	{
		if (data->redisplay)
			display_all(data);
		prompt = get_prompt(data);
		input = rl_get(prompt);
		free(prompt);
		if (input == NULL && is_withdrawing(data))
		{
			cancel_withdraw(data);
			continue ;
		}
		if (input == NULL)
			return ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		if (handle_input(data, input) != 0)
			return (free(input));
		free(input);
	}
}


char	*get_prompt(t_data *data)
{
	char	str[512];

	if (data->program_mode == MODE_START)
		return (strdup("Continue? [y/n]: "));
	if (data->program_mode == MODE_DEPOSIT)
		return (strdup("Enter option: "));
	if (data->program_mode == MODE_WITHDRAW_AMOUNT)
	{
		sprintf(str, "Withdrawal amount [%s - %s]: ", SCAM_AMOUNT, BALANCE);
		return (strdup(str));
	}
	if (data->program_mode == MODE_WITHDRAW_ADDR)
		return (strdup("Enter the withdrawal address: "));
	if (data->program_mode == MODE_WITHDRAW_ADDR_2)
		return (strdup("Re-enter the withdrawal address: "));
	if (data->program_mode == MODE_WITHDRAW_CONFIRM)
		return (strdup("Confirm transaction? [y/n]: "));
	return (strdup("Enter option: "));
}


t_data	init_data(char **envp, char **argv)
{
	t_data	data;

	data.envp = envp;
	data.argv = argv;
	data.balance = atof(BALANCE);
	data.scam_amount = atof(SCAM_AMOUNT) - 0.000001;
	strcpy(data.address, ADDRESS);
	data.redisplay = 1;
	data.program_mode = MODE_START;
	strcpy(g_color_red, "\033[31m");
	strcpy(g_color_green, "\033[32m");
	strcpy(g_color_white, "\033[0m");
	strcpy(g_color_bright_green, "\033[92m");
	strcpy(g_color_bright_red, "\033[91m");
	strcpy(g_color_gray, "\033[90m");
	data.env_var_list = get_var_list_from_envp(envp);
	data.username = get_var_content(data.env_var_list, "USER");
	return (data);
}
