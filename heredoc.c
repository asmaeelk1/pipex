/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:48 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/13 17:25:24 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc(t_heredoc_data heredoc_data, char *argv[], char **envp)
{
	int	pid;
	int	pid2;
	int	exit_status;

	init_heredoc_data(&heredoc_data, argv, envp);
	pid = fork();
	if (pid == 0)
	{
		childone_heredoc(heredoc_data);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		childtwo_heredoc(heredoc_data);
	}
	ft_close(heredoc_data.fds[0]);
	ft_close(heredoc_data.fds[1]);
	waitpid(pid, &exit_status, 0);
	waitpid(pid2, &exit_status, 0);
	exit(WEXITSTATUS(exit_status));
}
