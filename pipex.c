/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:20:41 by asel-kha          #+#    #+#             */
/*   Updated: 2024/02/24 01:25:19 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	childone(char *infile, char *cmd1, int fd[2], char **envp)
{
	int		ifile;
	char	*path;

	path = get_path(cmd1, envp);
	if(!path)
		exit(COMMAND_NOT_FOUND_ERROR);
	ifile = open(infile, O_RDONLY);
	if (ifile == -1)
		fatal(infile, "No such file or directory");
	ft_close(fd[0]);
	ft_dup2(ifile, 0);
	ft_dup2(fd[1], 1);
	ft_close(ifile);
	ft_close(fd[1]);
	execve(path, ft_split(cmd1, ' '), envp);
}

static void	childtwo(char *outfile, char *cmd2, int fd[2], char **envp)
{
	int		ofile;
	char	*path;

	path = get_path(cmd2, envp);
	if(!path)
		exit(COMMAND_NOT_FOUND_ERROR);
	ofile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!ofile)
		err();
	ft_close(fd[1]);
	ft_dup2(ofile, 1);
	ft_dup2(fd[0], 0);
	ft_close(ofile);
	ft_close(fd[0]);
	execve(path, ft_split(cmd2, ' '), envp);
}
void	at_exit(int *fd, pid_t fchild, pid_t schild)
{
	int	 exit_status;
	
	exit_status = 0;
	ft_close (fd[0]);
	ft_close(fd[1]);
	waitpid(fchild, &exit_status, 0);
	waitpid(schild, &exit_status, 0);
	exit(WEXITSTATUS(exit_status));
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	child1;
	pid_t	child2;
	
	if (ac != 5)
		printf("here\n"), fatal(BAD_ARG, EX_ARG);
	if (pipe(fd) < 0)
		err();
	child1 = fork();
	if (child1 < 0)
		err();
	if (child1 == 0)
		childone(av[1], av[2], fd, envp);
	child2 = fork();
	if (child2 < 0)
		err();
	if (child2 == 0)
		childtwo(av[4], av[3], fd, envp);
	at_exit(fd, child1, child2);
}
