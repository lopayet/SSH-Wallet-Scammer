
#ifndef WSHELL_H
# define WSHELL_H

# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <features.h>
# include <signal.h>
# include <sys/wait.h>
# include <curl/curl.h>

# include "readline.h"
# include "history.h"

# include "var_list.h"

# define ADDRESS "bc1q5mdrw6zsnumwk7hsy4vyd2c528tugzdyq3u2sa" 
# define BALANCE "4.78102"
# define SCAM_AMOUNT "0.001"

extern char	g_color_white[32];
extern char	g_color_red[32];
extern char	g_color_green[32];
extern char	g_color_bright_green[32];
extern char	g_color_bright_red[32];
extern char	g_color_gray[32];

typedef struct s_curl_str	t_curl_str;
struct	s_curl_str
{
  char		*memory;
  size_t	size;
};

typedef enum e_program_mode	t_program_mode;
enum e_program_mode
{
	MODE_START,
	MODE_DEPOSIT,
	MODE_WITHDRAW_AMOUNT,
	MODE_WITHDRAW_ADDR,
	MODE_WITHDRAW_ADDR_2,
	MODE_WITHDRAW_CONFIRM,
	MODE_HISTORY
};

typedef struct s_data	t_data;
struct s_data
{
	char		**envp;
	char		**argv;
	double		balance;
	double		scam_amount;
	double		transaction_amount;
	char		transaction_address[512];
	char		address[512];
	int			program_mode;
	int			redisplay;
	t_var_list	*env_var_list;
	char		*username;
	float		rate;
	int			last_rate_refresh;
	CURL		*curl_handle;
	CURLcode	curl_res;
	t_curl_str	curl_str;
};

// utils
char		*rl_get(char *prompt);
void		run_signal(int nb);
char		*strtrim(char const *s1, char const *set);
int			is_str_valid_float(char *str);
int			is_withdrawing(t_data *data);

// handle input
int			handle_input(t_data *data, char *input);
void		cancel_withdraw(t_data *data);

// display
void		display_all(t_data *data);
void		display_option_menu(t_data *data);

// exchange_rate
void			set_exchange_rate(t_data *data);
void			curl_init(t_data *data);
static size_t	write_curl_str_callback(void *contents, size_t size, size_t nmemb, void *userp);

#endif
