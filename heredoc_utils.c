/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:48 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/13 17:10:02 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_heredoc_data(t_heredoc_data *heredoc_data, char *argv[],
		char **envp)
{
	if (pipe(heredoc_data->fds) < 0)
		fatal("pipe", strerror(errno));
	heredoc_data->heredoc_file = "/tmp/heredoc";
	heredoc_data->delimiter = argv[2];
	heredoc_data->cmd1 = argv[3];
	heredoc_data->cmd2 = argv[4];
	heredoc_data->outfile = argv[5];
	heredoc_data->envp = envp;
}

static void	heredoc_exec(t_heredoc_data heredoc_data)
{
	int		heredoc;
	char	*tmp;

	heredoc = open(heredoc_data.heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (heredoc < 0)
	{
		err();
	}
	while (1)
	{
		write(1, ">> ", 2);
		tmp = get_next_line(0);
		if (!tmp || ((ft_strncmp(tmp, heredoc_data.delimiter,
						ft_strlen(heredoc_data.delimiter)) == 0)
				&& (ft_strlen(tmp) - 1 == ft_strlen(heredoc_data.delimiter))))
			break ;
		write(heredoc, tmp, ft_strlen(tmp));
		free(tmp);
	}
	free(tmp);
	ft_close(heredoc);
}

void	childone_heredoc(t_heredoc_data heredoc_data)
{
	int		ifile;
	char	*path;

	path = get_path(heredoc_data.cmd1, heredoc_data.envp);
	if (!path)
		exit(COMMAND_NOT_FOUND_ERROR);
	heredoc_exec(heredoc_data);
	ifile = open(heredoc_data.heredoc_file, O_RDONLY);
	if (ifile == -1)
	{
		fatal("open", strerror(errno));
	}
	ft_close(heredoc_data.fds[0]);
	ft_dup2(ifile, 0);
	ft_dup2(heredoc_data.fds[1], 1);
	ft_close(ifile);
	ft_close(heredoc_data.fds[1]);
	execve(path, ft_split(heredoc_data.cmd1, ' '), heredoc_data.envp);
}

void	childtwo_heredoc(t_heredoc_data heredoc_data)
{
	int		ofile;
	char	*path;

	path = get_path(heredoc_data.cmd2, heredoc_data.envp);
	if (!path)
		exit(COMMAND_NOT_FOUND_ERROR);
	ofile = open(heredoc_data.outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (!ofile)
		fatal("open: ", strerror(errno));
	ft_close(heredoc_data.fds[1]);
	ft_dup2(ofile, 1);
	ft_dup2(heredoc_data.fds[0], 0);
	ft_close(ofile);
	ft_close(heredoc_data.fds[0]);
	execve(path, ft_split(heredoc_data.cmd2, ' '), heredoc_data.envp);
}
