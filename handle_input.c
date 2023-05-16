
#include "wshell.h"


int	withdraw_amount_handle(t_data *data, char *input);
int	withdraw_address_handle(t_data *data, char *input);
void	cancel_withdraw(t_data *data);

int		handle_input(t_data *data, char *input)
{
	switch (data->program_mode)
	{
		case MODE_START:{
			if (!strcmp(input, "n") || !strcmp(input, "N"))
				return (1);
			else if (!strcmp(input, "y") || !strcmp(input, "Y"))
			{
				data->program_mode = MODE_DEPOSIT;
				data->redisplay = 1;
			}
			else
				printf("Please enter a valid option\n");
		}break;
		
		case MODE_DEPOSIT:
		case MODE_HISTORY:{
			if (!strcmp(input, "d") || !strcmp(input, "D"))
			{
				data->program_mode = MODE_DEPOSIT;
				data->redisplay = 1;
			}
			else if (!strcmp(input, "w") || !strcmp(input, "W"))
			{
				data->program_mode = MODE_WITHDRAW_AMOUNT;
				data->redisplay = 1;
			}
			else if (!strcmp(input, "r") || !strcmp(input, "R"))
			{
				data->program_mode = MODE_DEPOSIT;
				data->redisplay = 1;
			}
			else if (!strcmp(input, "h") || !strcmp(input, "H"))
			{
				data->program_mode = MODE_HISTORY;
				data->redisplay = 1;
			}
			else if (!strcmp(input, "e") || !strcmp(input, "E"))
				return (1);
			else
				printf("Please enter a valid option\n");
		}break;

		case MODE_WITHDRAW_AMOUNT:{
			if (withdraw_amount_handle(data, input) != 0)
				return (0);
			printf("\n");
			data->program_mode = MODE_WITHDRAW_ADDR;
		}break;

		case MODE_WITHDRAW_ADDR:{
			if (withdraw_address_handle(data, input) != 0)
				return (0);
			printf("\n");
			data->program_mode = MODE_WITHDRAW_ADDR_2;
		}break;

		case MODE_WITHDRAW_ADDR_2:{
			if (strcmp(input, data->transaction_address))
			{
				printf("%sError: addresses differ.%s\n", g_color_red, g_color_white);
				return (0);
			}
			data->program_mode = MODE_WITHDRAW_CONFIRM;
			printf("\nTransfering %s%.6f%s BTC to %s%s%s ...\n",
				g_color_green, data->transaction_amount, g_color_white,
				g_color_green, data->transaction_address, g_color_white);
		}break;

		case MODE_WITHDRAW_CONFIRM:{
			if ((!strcmp(input, "n") || !strcmp(input, "N"))
				|| (strcmp(input, "y") || strcmp(input, "Y")))
				return (cancel_withdraw(data), 0);
			sleep(3);
			printf("\n%sThe entered address is either an invalid BTC address, or it is not a confirmed withdrawal address for your account.%s\n",
				g_color_red, g_color_white);
			printf("If you would like to confirm this address you must deposit 0.001 BTC into your deposit address from the new withdrawal address.\n\
The sending address will validate as soon as the transaction is confirmed. This confirmation is typically instant.\n\
This process is an additional security measure for your account.\n\n");
			sleep(1);
			printf("Canceling...\n\n");
			data->program_mode = MODE_DEPOSIT;
			display_option_menu(data);
		}break;
	}
	return (0);
}

void	cancel_withdraw(t_data *data)
{
	printf("Canceling...\n");
	sleep(2);
	data->program_mode = MODE_DEPOSIT;
	data->redisplay = 1;
}

int	withdraw_amount_handle(t_data *data, char *input)
{
	float	amount;

	if (!is_str_valid_float(input))
	{
		printf("%sError: Invalid number format.%s\n", g_color_red, g_color_white);
		return (1);
	}
	amount = atof(input);
	if (amount > data->balance)
	{
		printf("%sError: Insufficient funds.%s\n", g_color_red, g_color_white);
		return (1);
	}
	if (amount < data->scam_amount)
	{
		printf("%sError: This account doesn't allow withdrawals under %s.%s\n", g_color_red, SCAM_AMOUNT, g_color_white);
		return (1);
	}
	data->transaction_amount = amount;
	return (0);
}

int	withdraw_address_handle(t_data *data, char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (!isalnum(input[i]))
		{
			printf("%sError: Invalid bitcoin address.%s\n", g_color_red, g_color_white);
			return (1);
		}
	}
	if ((strncmp(input, "bc1", 3)
	&& strncmp(input, "1", 1)
	&& strncmp(input, "3", 1)
	&& strncmp(input, "5", 1)
	&& strncmp(input, "K", 1)
	&& strncmp(input, "L", 1)
	&& strncmp(input, "M", 1)
	&& strncmp(input, "xpub", 4)
	&& strncmp(input, "xprv", 4)
	&& strncmp(input, "m", 1)
	&& strncmp(input, "n", 1)
	&& strncmp(input, "2", 1)
	&& strncmp(input, "9", 1)
	&& strncmp(input, "c", 1)
	&& strncmp(input, "tpub", 4)
	&& strncmp(input, "tprv", 4)
	&& strncmp(input, "tb1", 3))
	|| strlen(input) < 32
	|| strlen(input) > 80)
	{
		printf("%sError: Invalid bitcoin address.%s\n", g_color_red, g_color_white);
		return (1);
	}
	strcpy(data->transaction_address, input);
	return (0);
}


