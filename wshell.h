
#ifndef WSHELL_H
# define WSHELL_H

# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <features.h>
# include <signal.h>

# include "readline.h"
# include "history.h"

# include "var_list.h"

typedef enum e_program_mode	t_program_mode;
enum e_program_mode
{
	MODE_START,
	MODE_DEPOSIT,
	MODE_WITHDRAW_AMOUNT,
	MODE_WITHDRAW_ADDR,
	MODE_WITHDRAW_ADDR_2,
	MODE_HISTORY
};

typedef struct s_data	t_data;
struct s_data
{
	int			program_mode;
	int			clear_terminal;
	t_var_list	*env_var_list;
	char		*username;
};

// utils
char		*rl_get(char *prompt);
void		run_signal(int nb);
char		*strtrim(char const *s1, char const *set);

#endif
