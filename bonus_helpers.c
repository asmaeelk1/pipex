/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:02 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/21 22:59:11 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipex *data, char **av, int ac)
{
	int	i;

	data->infile = av[1];
	data->outfile = av[ac - 1];
	data->index_cmd = -1;
	data->command_number = ac - 3;
	data->pipe_number = 2 * (data->command_number - 1);
	data->pipe = malloc(sizeof(int) * data->pipe_number);
	i = -1;
	while (++i < data->command_number - 1)
	{
		if (pipe(data->pipe + 2 * i) == -1)
		{
			free_struct(data);
			fatal("pipe", strerror(errno));
		}
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			i;

	p = b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	free_struct(t_pipex *data)
{
	free(data->pipe);
}

void	ft_close_pipes(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < data->pipe_number)
		ft_close(data->pipe[i]);
}
