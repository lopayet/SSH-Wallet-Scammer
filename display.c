
#include "wshell.h"

void	display_start_header(t_data *data)
{
	int		username_len;
	int		i;

	username_len = strlen(data->username);
	printf("%s************************************", g_color_green);
	i = username_len + 1;
	while (--i > 0)
		printf("*");
	printf("***\n");
	printf("** Welcome back to your SSH wallet, %s **\n", data->username);
	printf("************************************");
	i = username_len + 1;
	while (--i > 0)
		printf("*");
	printf("***%s\n\n", g_color_white);
	printf("%s\
You are currently not using 2FA, this is a major security risk!\n\
 • Please configure 2FA through the desktop application.\n\
 • We highly recommend locking all transactions until 2FA is configured.\n\
 • You currently have transactions: %sEnabled%s\n\n", g_color_red, g_color_green, g_color_white);
}

void	display_bitcoin_balance(t_data *data)
{
	printf("BTC Balance: %s%f ($129489.17)%s\n\n", g_color_bright_green, data->balance, g_color_white);
}

void	display_deposit_address(t_data *data)
{
	printf("Your deposit address is: %s%s%s\n\n", g_color_bright_green, data->address, g_color_white);
}

void	display_option_menu(t_data *data)
{
	printf("\
(D)eposit\n\
(W)ithdraw\n\
(R)efresh USD Rate\n\
(H)istory\n\
(E)xit\n\n");
}


void	display_default_header(t_data *data)
{
	int		username_len;
	int		i;

	username_len = strlen(data->username);
	printf("%s*****************", g_color_green);
	i = username_len + 1;
	while (--i > 0)
		printf("*");
	printf("***\n");
	printf("** Logged in as: %s **\n", data->username);
	printf("*****************");
	i = username_len + 1;
	while (--i > 0)
		printf("*");
	printf("***%s\n\n", g_color_white);
	printf("%s\
Note: The SSH terminal is still in beta, and as such not all options are available.\n\
We heavily recommend using the desktop app. Use at your own risk.%s\n\n", g_color_bright_red, g_color_white);
	display_bitcoin_balance(data);
}

void	display_history(t_data *data)
{

	printf("\
%sOnly transactions over 0.001 BTC are displayed here.\n\
%sDate       Type         Address         Amount.%s\n", g_color_red, g_color_gray, g_color_white);

	printf("\
01/07/23   Withdrawal   %sBC1Q....2V3N*%s   %s1.02975121%s\
\n", g_color_green, g_color_white, g_color_red, g_color_white);

	printf("\
11/17/21   Deposit      %sBC1Q....2V3N*%s   %s0.00129562%s\
\n", g_color_green, g_color_white, g_color_green, g_color_white);

	printf("\
08/20/21   Deposit      %sBC19....KaK4*%s   %s2.50526414%s\
\n", g_color_green, g_color_white, g_color_green, g_color_white);

	printf("\
07/27/20   Withdrawal   %sBC1b....n6A5*%s   %s0.58330482%s\
\n", g_color_green, g_color_white, g_color_red, g_color_white);

	printf("\
04/01/19   Deposit      %sBC1b....n6A5*%s   %s0.00100000%s\
\n", g_color_green, g_color_white, g_color_green, g_color_white);

	printf("\
11/26/19   Deposit      %sBC19....KaK4*%s   %s0.83909679%s\
\n", g_color_green, g_color_white, g_color_green, g_color_white);

	printf("\
01/21/18   Withdrawal   %sBC1Q....dDer*%s   %s1.33548585%s\
\n", g_color_green, g_color_white, g_color_red, g_color_white);

	printf("\
01/19/18   Deposit      %sBC1Q....dDer*%s   %s0.00100000%s\
\n", g_color_green, g_color_white, g_color_green, g_color_white);

	printf("\
06/23/17   Deposit      %sBC19....KaK4*%s   %s1.32548585%s\
\n", g_color_green, g_color_white, g_color_green, g_color_white);

	printf("\
03/08/15   Deposit      %sBC1Q....Yb2d*%s   %s3.02675472%s\
\n", g_color_green, g_color_white, g_color_green, g_color_white);

	printf("\n* = Address confirmed for withdrawals.\n\n");
}

void	clear_terminal(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("\e[2J\e[H");
		return ;
	}
	if (pid == 0)
	{
		if (execve("/usr/bin/clear", data->argv, data->envp))
		{
			printf("\e[2J\e[H");
			return ;
		}
	}
	else
		wait(NULL);
}

void	display_all(t_data *data)
{
	clear_terminal(data);

	if (data->program_mode == MODE_START)
		display_start_header(data);
	else
		display_default_header(data);

	if (data->program_mode == MODE_DEPOSIT)
	{
		display_deposit_address(data);
		display_option_menu(data);
	}
	if (data->program_mode == MODE_HISTORY)
	{
		display_history(data);
		display_option_menu(data);
	}
	if (data->program_mode == MODE_WITHDRAW_AMOUNT)
		printf("Use ctrl+d to cancel withdraw.\n");
	data->redisplay = 0;
}
