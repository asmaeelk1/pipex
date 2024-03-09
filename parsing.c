/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:14:46 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/08 20:14:08 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_path(char **paths, char *cmd)
{
	char	*part_path;
	char	*path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	**command;
	char	**command_args;

	i = 0;
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		command_args = ft_split(cmd, ' ');
		if (access(command_args[0], X_OK) == 0)
		{
			path = ft_strdup(command_args[0]);
			return (ft_free(command_args), path);
		}
		return (ft_free(command_args), NULL);
	}
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	command = ft_split(cmd, ' ');
	paths = ft_split(envp[i] + 5, ':');
	path = join_path(paths, command[0]);
	if (path)
		return (ft_free(paths), path);
	return (ft_free(paths), NULL);
}
