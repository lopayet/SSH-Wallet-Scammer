
#include "wshell.h"

void	log_line(t_data *data, char *input)
{
	strlcat(data->log_str, input, LOG_STR_SIZE);
	strlcat(data->log_str, "\n", LOG_STR_SIZE);
}

void	log_session(t_data *data)
{
	char	filepath[512];
	int		fd;

	strcpy(filepath, LOG_FILE);
	fd = open(filepath, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd < 0)
		return ;
	dprintf(fd, "--------\nConnection ended (%s):\n%s\n", data->username, data->log_str);
	close(fd);
}
