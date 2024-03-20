/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:14:46 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/20 00:48:30 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_first_command(t_pipex data, char *first_cmd, char **envp)
{
	int		ifile;
	char	*path;

	ifile = open(data.infile, O_RDONLY);
	if (ifile == -1)
		fatal(data.infile, strerror(errno));
	path = get_path(first_cmd, envp);
	if (!path)
		fatal(first_cmd, "\033[31mcommand not found");
	ft_dup2(ifile, 0);
	ft_dup2(data.pipe[1], 1);
	ft_close(ifile);
	ft_close_pipes(&data);
	if (execve(path, ft_split(first_cmd, ' '), envp) == -1)
		fatal("Execve:", strerror(errno));
}

void	handle_last_command(t_pipex data, char *last_cmd, char **envp)
{
	int		ofile;
	char	*path;

	path = get_path(last_cmd, envp);
	if (!path)
		err();
	ofile = open(data.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!ofile)
		fatal("open: ", strerror(errno));
	ft_dup2(ofile, 1);
	ft_dup2(data.pipe[2 * data.index_cmd - 2], 0);
	ft_close(ofile);
	ft_close_pipes(&data);
	if (execve(path, ft_split(last_cmd, ' '), envp) == -1)
		fatal("Execve:", strerror(errno));
}

void	ft_dup2_bonus(int file0, int file1)
{
	if (dup2(file0, 0) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(file1, 1) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}
