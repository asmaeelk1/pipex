/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:23:18 by asel-kha          #+#    #+#             */
/*   Updated: 2024/02/24 01:48:44 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libc.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>

# define COMMAND_NOT_FOUND_ERROR 127
# define BAD_ARG "Error: Bad arguments\n"
# define EX_ARG  "Ex: ./pipex <file1> <cmd1> <cmd2> <file2>"
# define EX_ARG_BONUS  "Ex: ./pipex <file1> <cmd1> <cmd2> ... <cmdn> <file2>"

typedef struct s_pipex
{
	int ofile;
	int ifile;
	int index_cmd;
	int pipe_number;
	char *true_path;
}	t_pipex;


void	err(void);
void	ft_close(int file);
size_t	ft_strlen(const char *c);
void	ft_dup2(int file, int fd);
char	*ft_strdup(const char *s1);
char	*get_path(char *cmd, char **envp);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	*ft_calloc( size_t count, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
void	fatal(const char *command, const char *msg);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	init_struct(t_pipex *data, char **av, int ac);
void	child_processe(t_pipex *data, int fd[2], char **av, char **envp);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif
