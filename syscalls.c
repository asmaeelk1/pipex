/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:42:58 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/14 03:52:16 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup2(int file, int fd)
{
	if (dup2(file, fd) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
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

void	ft_close(int file)
{
	if (close(file) < 0)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}
