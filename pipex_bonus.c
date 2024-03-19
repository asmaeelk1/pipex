/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:48 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/15 02:09:22 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_pipex *data, char **av, int ac, char **envp)
{
	data->pid = fork();
	if (data->pid == 0)
	{
		if (data->index_cmd == 0)
			handle_first_command(*data, av[2], envp);
		else if (data->index_cmd == data->command_number - 1)
			handle_last_command(*data, av[ac - 2], envp);
		ft_dup2_bonus(data->pipe[2 * data->index_cmd - 2], data->pipe[2
			* data->index_cmd + 1]);
		ft_close_pipes(data);
		data->true_path = get_path(av[data->index_cmd + 2], envp);
		if (!data->true_path)
			exit(COMMAND_NOT_FOUND_ERROR);
		if (execve(data->true_path, ft_split(av[data->index_cmd + 2], ' '),
				envp) == -1)
			fatal("Execve:", "falure");
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex			data;
	t_heredoc_data	heredoc_data;
	int				state;

	if (ac < 5)
		fatal(BAD_ARG, EX_ARG_BONUS);
	ft_memset(&heredoc_data, 0, sizeof(heredoc_data));
	ft_memset(&data, 0, sizeof(data));
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		heredoc(heredoc_data, av, envp);
		return (0);
	}
	init_struct(&data, av, ac);
	while (++data.index_cmd < data.command_number)
		child(&data, av, ac, envp);
	ft_close_pipes(&data);
	while (waitpid(data.pid, &state, 0) != -1)
		;
	exit(WEXITSTATUS(state));
}
