/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 01:50:25 by asel-kha          #+#    #+#             */
/*   Updated: 2024/02/24 04:25:22 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipex *data, char **av, int ac)
{
	data->index_cmd = 1;
	if ((data->ifile = open(av[1], O_RDONLY, 0644)) == -1)
		err();
	if ((data->ofile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644)) == -1)
		err();
}

void	create_pipe(char **av, t_pipex *data, char **envp)
{
	int fd[2];
	pid_t	child;
	if(pipe(fd) < 0)
		err();
	child = fork();
	if(child < 0)
		err();
	if(child == 0)
	{
		ft_close(fd[0]);
		ft_dup2(fd[1], 1);
		data->true_path = get_path(av[data->index_cmd], envp);
		if(!data->true_path)
			exit(COMMAND_NOT_FOUND_ERROR);
		if ((execve(data->true_path, ft_split(av[data->index_cmd], ' '), envp)) == -1)
			fatal(av[data->index_cmd], "command not found");
	}
	else
	{
		ft_close(fd[1]);
		ft_dup2(fd[0], 0);
	}
}

int main(int ac, char **av, char **envp)
{
	t_pipex data;

	if(ac < 5)
		fatal(BAD_ARG, EX_ARG_BONUS);
	init_struct(&data, av, ac);
	ft_dup2(data.ifile, 0);
	while(++data.index_cmd < ac - 2)
		create_pipe(av, &data, envp);
	ft_dup2(data.ofile, 1);
	data.true_path = get_path(av[data.index_cmd], envp);
	if ((execve(data.true_path, ft_split(av[data.index_cmd], ' '), envp)) == -1)
		fatal(av[data.index_cmd], "command not found");
	
}
