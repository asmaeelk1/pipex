/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:22 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/17 21:30:03 by asel-kha         ###   ########.fr       */
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
