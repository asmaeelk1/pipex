
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

void	child(t_pipex data, char **av, char **envp)
{
	data.pid = fork();
	if (data.pid == 0)
	{
		if (data.index_cmd == 0)
			ft_dup2_bonus(data.ifile, data.pipe[1]);
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
		child(data, av, envp);
	ft_close_pipes(&data);
	ft_close(data.ifile);
	ft_close(data.ofile);
	while (waitpid(data.pid, &state, 0) != -1)
		;
	exit(WEXITSTATUS(state));
}