/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 01:59:59 by asel-kha          #+#    #+#             */
/*   Updated: 2024/02/23 02:01:49 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <libc.h>
# include <stdio.h>

# define BAD_ARG "Error: Bad arguments\n"
# define EX_ARG  "Ex: ./pipex <file1> <cmd1> <cmd2>... <cmdn> <file2>"
# define COMMAND_NOT_FOUND_ERROR 127

void	fatal(const char *command, const char *msg);

# endif