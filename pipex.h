/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:23:18 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/20 00:42:48 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <unistd.h>

# define COMMAND_NOT_FOUND_ERROR 127
# define BAD_ARG "\033[31mError: Bad arguments\n"
# define EX_ARG "\033[37mEx: ./pipex <file1> <cmd1> <cmd2> <file2>"
# define EX_ARG_BONUS "\033[37mEx: ./pipex_bonus  <file1><cmd1><cmd2>...<cmdn><file2>"
# define EX_ARG_HEREDOC "\033[37mEx: ./pipex_bonus here_doc DEL cmd1 cmd2 <outfile>"

typedef struct s_heredoc_data	t_heredoc_data;

struct s_heredoc_data
{
	char	*delimiter;
	char	*cmd1;
	char	*cmd2;
	char	*path1;
	char	*path2;
	char	*outfile;
	char	*heredoc_file;
	int		fds[2];
	char	**envp;
};

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
}			t_pipex;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

// parsing.c
char	*get_path(char *cmd, char **envp);

//bonus_helpers2.c
void	handle_first_command(t_pipex data, char *first_cmd, char **envp);
void	handle_last_command(t_pipex data, char *last_cmd, char **envp);
void	ft_dup2_bonus(int file0, int file1);

// heredoc.c
void	heredoc(t_heredoc_data heredoc_data,
			char *argv[], char **envp);

// heredoc_utils.c
void	init_heredoc_data(t_heredoc_data *heredoc_data,
			char *argv[], char **envp);
void	childone_heredoc(t_heredoc_data heredoc_datas);
void	childtwo_heredoc(t_heredoc_data heredoc_datas);

// bonus_helpers.c
void	init_struct(t_pipex *data, char **av, int ac);
void	*ft_memset(void *b, int c, size_t len);
void	ft_close_pipes(t_pipex *data);
void	free_struct(t_pipex *data);

// pipex_helpers.c
char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *c);
char	*ft_strnstr(const char *haystack,
			const char *needle, size_t len);
char	*ft_strdup(const char *s1);

//pipex_helpers2.c
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
size_t	ft_strlcpy(char *dst, const char *src,
			size_t dstsize);
int		ft_strncmp(char *s1, char *s2, size_t n);

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, unsigned int start,
			size_t len);

// syscalls.c
void	ft_dup2(int file, int fd);
void	ft_close(int file);

// errors.c
void	err(void);
void	fatal(const char *command, const char *msg);

// ft_split.c
char	**ft_split(char *s, char c);

// void							child_processe(t_pipex *data, int fd[2],
// 									char **av, char **envp);

#endif
