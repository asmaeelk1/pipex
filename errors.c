/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:42:58 by asel-kha          #+#    #+#             */
/*   Updated: 2024/02/24 02:07:19 by asel-kha         ###   ########.fr       */
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

void	ft_close(int file)
{
	if (close(file) < 0)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}

void	err(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	fatal(const char *command, const char *msg)
{
	ft_putstr_fd(command, 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
