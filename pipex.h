/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:23:18 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/13 15:37:12 by asel-kha         ###   ########.fr       */
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
# include <sys/errno.h>

# define COMMAND_NOT_FOUND_ERROR 127
# define BAD_ARG "\033[31mError: Bad arguments\n"
# define EX_ARG  "\033[37mEx: ./pipex <file1> <cmd1> <cmd2> <file2>"
# define EX_ARG_BONUS  "\033[37mEx: ./pipex <file1><cmd1><cmd2>...<cmdn><file2>"

typedef struct s_heredoc_data t_heredoc_data;

struct s_heredoc_data {
	char *delimiter;
	char *cmd1;
	char *cmd2;
	char *path1;
	char *path2;
	char *outfile;
	char *heredoc_file;
	char **envp;
};

void	childone_heredoc(char *infile, char *cmd1, int fd[2], char **envp, char *delim);

typedef struct s_pipex
{
	int		index_cmd;
	int		command_number;
	int		*pipe;
	pid_t	pid;
	int		pipe_number;
	char	*true_path;
	char	*infile;
	char	*outfile;
}	t_pipex;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

void	heredoc(int ac, char *argv[], char **envp);
void	childtwo_heredoc(char *outfile, char *cmd2, int fd[2], char **envp);

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);

int	ft_strncmp( char *s1, char *s2, size_t n);

void	init_struct(t_pipex *data, char **av, int ac);
void free_struct(t_pipex *data);
void create_pipes(t_pipex *data);
void ft_close_pipes(t_pipex *data);

void	err(void);
void	ft_close(int file);
size_t	ft_strlen(const char *c);
void	ft_dup2(int file, int fd);
void 	ft_dup2_bonus(int file0, int file1);
char	*ft_strdup(const char *s1);
char	*get_path(char *cmd, char **envp);
char	**ft_split(char  *s, char c);
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
