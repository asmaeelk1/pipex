/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:48 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/09 21:51:07 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	heredoc(t_pipex *data, char *delemiter)
{
	int		fd;
	char	*tmp;

	fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		err();
	while (1)
	{
		write(1, ">> ", 2);
		tmp = get_next_line(0);
		if (!tmp || ((ft_strncmp(tmp, delemiter, ft_strlen(delemiter)) == 0)
				&& (ft_strlen(tmp) - 1 == ft_strlen(delemiter))))
			break ;
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	if (*delemiter == '\n')
		free(delemiter);
	free(tmp);
	ft_close(fd);
	data->ifile = open("heredoc", O_RDONLY, 0644);
	unlink("heredoc");
	if (data->ifile < 0)
		err();
}

void handle_first_command(t_pipex data, char *cmd1, char **envp)
{
	int		ifile;
	char	*path;

	path = get_path(cmd1, envp);
	if (!path)
		exit(COMMAND_NOT_FOUND_ERROR);
	ifile = open(data.infile, O_RDONLY);
	if (ifile == -1)
	{
		fatal(data.infile, strerror(errno));
	}
	ft_close(data.pipe[0]);
	ft_dup2(ifile, 0);
	ft_dup2(data.pipe[1], 1);
	ft_close(ifile);
	ft_close(data.pipe[1]); 
	execve(path, ft_split(cmd1, ' '), envp);
}

void	handle_last_command(t_pipex data, char *last_cmd, char **envp)
{
	int		ofile;
	char	*path;

	path = get_path(last_cmd, envp);
	if (!path)
		exit(COMMAND_NOT_FOUND_ERROR);
	ofile = open(data.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!ofile)
		fatal("open: ", strerror(errno));
	ft_close(data.pipe[2 * data.index_cmd + 1]);
	ft_dup2(ofile, 1);
	ft_dup2(data.pipe[2 * data.index_cmd - 2], 0);
	ft_close(ofile);
	ft_close(data.pipe[2 * data.index_cmd + 1]);
	execve(path, ft_split(last_cmd, ' '), envp);
}

void	child(t_pipex data,  char **av, int ac, char **envp)
{
	data.pid = fork();
	if (data.pid == 0)
	{
		if (data.index_cmd == 0)
		{
			handle_first_command(data, av[2], envp);
		}
		else if (data.index_cmd == data.command_number - 1)
			handle_last_command(data, av[ac - 2], envp);
			// ft_dup2_bonus(data.ifile, data.pipe[1]);
		else if (data.index_cmd == data.command_number - 1)
			ft_dup2_bonus(data.pipe[2 * data.index_cmd - 2], data.ofile);
		else
			ft_dup2_bonus (data.pipe[2 * data.index_cmd - 2],
				data.pipe[2 * data.index_cmd + 1]);
		ft_close_pipes(&data);
		data.true_path = get_path(av[data.index_cmd + 2 + data.heredoc], envp);
		if (!data.true_path)
			exit(COMMAND_NOT_FOUND_ERROR);
		if (execve(data.true_path, ft_split(av[data.index_cmd + 2 + data.heredoc], ' '),
				envp) == -1)
			fatal("Execve:", "falure");
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	int		state;

	if (ac < 5)
		fatal(BAD_ARG, EX_ARG_BONUS);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
		data.heredoc = 1;
	else
		data.heredoc = 0;
	init_struct(&data, av, ac);
	data.index_cmd = -1;
	data.command_number = ac - 3 - data.heredoc;
	data.pipe_number = 2 * (data.command_number - 1);
	data.pipe = malloc(sizeof(int *) * data.pipe_number);
	create_pipes(&data);
	while (++data.index_cmd < data.command_number)
		child(data, av, ac, envp);
	ft_close_pipes(&data);
	ft_close(data.ifile);
	ft_close(data.ofile);
	while (waitpid(data.pid, &state, 0) != -1)
		;
	exit(WEXITSTATUS(state));
}
