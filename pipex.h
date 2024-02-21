/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:23:18 by asel-kha          #+#    #+#             */
/*   Updated: 2024/02/20 19:29:01 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <libc.h>
# include <stdio.h>

# define BAD_ARG "Error: Bad arguments\n"
# define EX_ARG  "Ex: ./pipex <file1> <cmd1> <cmd2> <file2>"
# define COMMAND_NOT_FOUND_ERROR 127

char	**ft_split(char const *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_calloc( size_t count, size_t size);
char	*get_path(char *cmd, char **envp);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	err(void);
void	fatal(const char *command, const char *msg);
void	ft_dup2(int file, int fd);
void	ft_close(int file);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);

#endif
