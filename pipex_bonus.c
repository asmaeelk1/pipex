/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:48 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/13 15:36:54 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	heredoc_exec( char *delemiter)
{
	int		heredoc;
	char	*tmp;

	heredoc = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (heredoc < 0) {
		err();
	}
	while (1)
	{
		write(1, ">> ", 2);
		tmp = get_next_line(0);
		if (!tmp || ((ft_strncmp(tmp, delemiter, ft_strlen(delemiter)) == 0)
				&& (ft_strlen(tmp) - 1 == ft_strlen(delemiter))))
			break ;
		write(heredoc, tmp, ft_strlen(tmp));
		free(tmp);
	}
	// if (*delemiter == '\n')
	// 	free(delemiter);
	free(tmp);
	ft_close(heredoc);
	// heredoc = open("/tmp/heredoc", O_RDONLY, 0644);
	// unlink("/tmp/heredoc");
	// if (heredoc < 0)
	// 	err();
}

void	handle_first_command(t_pipex data, char *cmd1, char **envp)
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
		// printf("Child PID: %i\n", getpid());
		if (data.index_cmd == 0)
			handle_first_command(data, av[2], envp);
		else if (data.index_cmd == data.command_number - 1)
			handle_last_command(data, av[ac - 2], envp);
		else
			ft_dup2_bonus (data.pipe[2 * data.index_cmd - 2],
				data.pipe[2 * data.index_cmd + 1]);
		ft_close_pipes(&data);
		data.true_path = get_path(av[data.index_cmd + 2], envp);
		if (!data.true_path)
			exit(COMMAND_NOT_FOUND_ERROR);
		// while(1);
		if (execve(data.true_path, ft_split(av[data.index_cmd + 2], ' '),
				envp) == -1)
			fatal("Execve:", "falure");
	}
}


#include <string.h>
// ./pipex here_doc del cm1 cmd2 outfile
void init_heredoc_data(t_heredoc_data *heredoc_data, char *argv[], char **envp)
{
	heredoc_data->heredoc_file = "/tmp/heredoc";
	heredoc_data->delimiter = argv[2];
	heredoc_data->cmd1 = argv[3];
	heredoc_data->cmd2 = argv[4];
	heredoc_data->outfile = argv[5];
}
void	childtwo_heredoc(char *outfile, char *cmd2, int fd[2], char **envp)
{
	int		ofile;
	char	*path;

	path = get_path(cmd2, envp);
	if (!path)
		exit(COMMAND_NOT_FOUND_ERROR);
	ofile = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (!ofile)
		fatal("open: ", strerror(errno));
	ft_close(fd[1]);
	ft_dup2(ofile, 1);
	ft_dup2(fd[0], 0);
	ft_close(ofile);
	ft_close(fd[0]);
	execve(path, ft_split(cmd2, ' '), envp);
}
// ./pipex here_doc del cm1 cmd2 outfile
// cmd1 << LIMITER | cmd2 >> file


void	childone_heredoc(char *infile, char *cmd1, int fd[2], char **envp, char *delim)
{
	int		ifile;
	char	*path;

	path = get_path(cmd1, envp);
	if (!path)
		exit(COMMAND_NOT_FOUND_ERROR);
	heredoc_exec(delim);
	ifile = open(infile, O_RDONLY);
	if (ifile == -1) {
		puts("HELLJKA");
		fatal(infile, strerror(errno));
	}
	ft_close(fd[0]);
	ft_dup2(ifile, 0);
	ft_dup2(fd[1], 1);
	ft_close(ifile);
	ft_close(fd[1]);
	execve(path, ft_split(cmd1, ' '), envp);
}

void	heredoc(int ac, char *argv[], char **envp)
{
	t_heredoc_data	heredoc_data;
	int pid;
	int pid2;

	int heredoc_pipe[2];
	if (pipe(heredoc_pipe) < 0)
		fatal("pipe", strerror(errno));
	memset(&heredoc_data, 0, sizeof(heredoc_data));
	init_heredoc_data(&heredoc_data, argv, envp);

	pid = fork();
	if (pid == 0) {
		childone_heredoc(heredoc_data.heredoc_file, heredoc_data.cmd1, heredoc_pipe, envp, heredoc_data.delimiter);
	}
	pid2 = fork();
	if (pid2 == 0) {
		childtwo_heredoc(heredoc_data.outfile, heredoc_data.cmd2, heredoc_pipe, envp);
	}
	int exit_status;
	ft_close(heredoc_pipe[0]);
	ft_close(heredoc_pipe[1]);
	waitpid(pid, &exit_status, 0);
	waitpid(pid2, &exit_status, 0);
	exit(WEXITSTATUS(exit_status));
}

int	main(int ac, char **av, char **envp)
{
	// printf("Parent PID: %i\n", getpid());
	t_pipex	data;
	int		state;

	if (ac < 5)
		fatal(BAD_ARG, EX_ARG_BONUS);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0) {
		heredoc(ac, av, envp);
		return 0;
	}
	init_struct(&data, av, ac);
	while (++data.index_cmd < data.command_number)
		child(data, av, ac, envp);
	ft_close_pipes(&data);
	while (waitpid(data.pid, &state, 0) != -1)
		;
	// getchar();
	exit(WEXITSTATUS(state));
}
