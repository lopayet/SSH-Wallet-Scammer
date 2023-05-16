
#include "wshell.h"

char	g_color_white[32];
char	g_color_red[32];
char	g_color_green[32];

void	wshell(t_data *data);
char	*get_prompt(t_data *data);
t_data	init_data(char **envp);
void	display_start_header(t_data data);
void	display_basic_header(t_data data);
int		handle_input(t_data *data, char *input);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
		return (1);
	(void) argv;
	data = init_data(envp);
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
		prompt = get_prompt(data);
		input = rl_get(prompt);
		free(prompt);
		if (input == NULL)
			return ;
		if (handle_input(data, input) != 0)
			return (free(input));
		free(input);
	}
}



int		handle_input(t_data *data, char *input)
{
	switch (data->program_mode)
	{
		case MODE_START:{
			if (!strcmp(input, "n") || !strcmp(input, "N"))
				return (1);
			else if (!strcmp(input, "y") || !strcmp(input, "Y"))
				data->program_mode = MODE_DEPOSIT;
			else
				printf("Please enter a valid option\n");
		}break;
		
		case MODE_DEPOSIT:
		case MODE_HISTORY:{
			if (!strcmp(input, "d") || !strcmp(input, "D"))
				data->clear_terminal = 1;
			else if (!strcmp(input, "w") || !strcmp(input, "W"))
			{
				data->program_mode = MODE_WITHDRAW_AMOUNT;
				data->clear_terminal = 1;
			}
			else if (!strcmp(input, "r") || !strcmp(input, "R"))
				data->clear_terminal = 1;
			else if (!strcmp(input, "h") || !strcmp(input, "H"))
			{
				data->program_mode = MODE_HISTORY;
				data->clear_terminal = 1;
			}
			else if (!strcmp(input, "e") || !strcmp(input, "E"))
				return (1);
			else
				printf("Please enter a valid option\n");
		}break;

		case MODE_WITHDRAW_AMOUNT:{
		}break;
		
		case MODE_WITHDRAW_ADDR:{
		}break;
		
		case MODE_WITHDRAW_ADDR_2:{
		}break;
	}
	return (0);
}


char	*get_prompt(t_data *data)
{
	if (data->program_mode == MODE_START)
		return (strdup("Continue? [y/n]: "));
	if (data->program_mode == MODE_DEPOSIT)
		return (strdup("Enter option: "));
	if (data->program_mode == MODE_WITHDRAW_AMOUNT)
		return (strdup("Withdrawal amount [0.001 - 4.78102]: "));
	if (data->program_mode == MODE_WITHDRAW_ADDR)
		return (strdup("Enter the withdrawal address: "));
	if (data->program_mode == MODE_WITHDRAW_ADDR_2)
		return (strdup("Re-enter the withdrawal address: "));
	return (strdup("Enter option: "));
}


t_data	init_data(char **envp)
{
	t_data	data;

	data.clear_terminal = 1;
	data.program_mode = MODE_START;
	strcpy(g_color_red, "\033[31m");
	strcpy(g_color_green, "\033[32m");
	strcpy(g_color_white, "\033[0m");
	data.env_var_list = get_var_list_from_envp(envp);
	data.username = get_var_content(data.env_var_list, "USER");
	return (data);
}

void	display_start_header(t_data data)
{
	int		username_len;
	int		i;

	username_len = strlen(data.username);
	printf("%s************************************", g_color_green);
	i = username_len + 1;
	while (--i > 0)
		printf("*");
	printf("***\n");
	printf("** Welcome back to your SSH wallet, %s **\n", data.username);
	printf("************************************");
	i = username_len + 1;
	while (--i > 0)
		printf("*");
	printf("***%s\n", g_color_white);
}

void	display_basic_header(t_data data)
{
	int		username_len;
	int		i;

	username_len = strlen(data.username);
	printf("%s*****************", g_color_green);
	i = username_len + 1;
	while (--i > 0)
		printf("*");
	printf("***\n");
	printf("** Logged in as: %s **\n", data.username);
	printf("*****************");
	i = username_len + 1;
	while (--i > 0)
		printf("*");
	printf("***%s\n", g_color_white);
}
