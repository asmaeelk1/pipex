
#include "pipex.h"

void	err(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	fatal(const char *command, const char *msg)
{
	ft_putstr_fd(command, 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
