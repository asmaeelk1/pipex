/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 01:50:25 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/07 20:35:09 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipex *data, char **av, int ac)
{
	if (data->heredoc == 1)
		heredoc(data, av[2]);
	else
	{
		data->ifile = open(av[1], O_RDONLY, 0644);
		if (data->ifile == -1)
			err();
	}
	if (data->heredoc == 1)
	{
		data->ofile = open(av[ac - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
		if (data->ofile == -1)
			err();
	}
	else
	{
		data->ofile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (data->ofile == -1)
			err();
	}
}

void	free_struct(t_pipex *data)
{
	if (close(data->ofile) == -1)
		ft_close(data->ofile);
	if (close(data->ifile) == -1)
		ft_close(data->ifile);
}

void	create_pipes(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < data->command_number - 1)
		if (pipe(data->pipe + 2 * i) == -1)
			free_struct(data);
}

void	ft_close_pipes(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < data->pipe_number)
		ft_close(data->pipe[i]);
}
