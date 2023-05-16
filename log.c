
#include "wshell.h"

void	log_line(t_data *data, char *input)
{
	strlcat(data->log_str, input, LOG_STR_SIZE);
	strlcat(data->log_str, "\n", LOG_STR_SIZE);
}

void	log_session(t_data *data)
{
	char	filepath[512];
	char	*home_dir;
	int		fd;

	home_dir = get_var_content(data->env_var_list, "HOME");
	strcpy(filepath, home_dir);
	strcat(filepath, "/wshell_log.txt");
	fd = open(filepath, O_WRONLY | O_APPEND | O_CREAT, 0640);
	if (fd < 0)
		return ;
	dprintf(fd, "--------\nConnection ended:\n%s\n--------\n\n", data->log_str);
	close(fd);
}
