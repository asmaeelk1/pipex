/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:48 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/20 09:46:38 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	heredoc_exec(t_heredoc_data heredoc_data)
{
	char	*tmp;
	int		tempfile_fd;

	tempfile_fd = open(heredoc_data.heredoc_file, O_CREAT | O_RDWR | O_TRUNC,
			0644);
	if (tempfile_fd == -1)
		fatal("open: ", strerror(errno));
	while (1)
	{
		write(1, ">> ", 3);
		tmp = get_next_line(0);
		if (!tmp || ((ft_strncmp(tmp, heredoc_data.delimiter,
						ft_strlen(heredoc_data.delimiter)) == 0)
				&& (ft_strlen(tmp) - 1 == ft_strlen(heredoc_data.delimiter))))
			break ;
		write(tempfile_fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	free(tmp);
	ft_close(tempfile_fd);
}

void	heredoc(t_heredoc_data heredoc_data, char *argv[], char **envp)
{
	int	pid;
	int	pid2;
	int	exit_status;

	init_heredoc_data(&heredoc_data, argv, envp);
	heredoc_exec(heredoc_data);
	pid = fork();
	if (pid == 0)
		childone_heredoc(heredoc_data);
	waitpid(pid, &exit_status, 0);
	pid2 = fork();
	if (pid2 == 0)
		childtwo_heredoc(heredoc_data);
	ft_close(heredoc_data.fds[0]);
	ft_close(heredoc_data.fds[1]);
	waitpid(pid2, &exit_status, 0);
	exit(WEXITSTATUS(exit_status));
}
