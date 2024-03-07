/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:42:58 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/07 09:39:35 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
