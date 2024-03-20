/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:14:46 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/20 08:35:53 by asel-kha         ###   ########.fr       */
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

char	*ft_getenv(char **envp, char *key)
{
	int		index;
	size_t	key_len;

	index = 0;
	key_len = strlen(key);
	while (envp[index] && strncmp(envp[index], key, key_len) != 0)
	{
		index++;
	}
	if (envp[index] == NULL)
	{
		return (NULL);
	}
	return (strdup(envp[index] + 5));
}

char	*relative_path(char *cmd)
{
	char	**command_args;
	char	*path;

	command_args = NULL;
	path = NULL;
	command_args = ft_split(cmd, ' ');
	if (access(command_args[0], X_OK) == 0)
	{
		path = ft_strdup(command_args[0]);
		return (ft_free(command_args), path);
	}
	return (ft_free(command_args), NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	**command;
	char	*env_value;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (relative_path(cmd));
	env_value = ft_getenv(envp, "PATH=");
	if (env_value == NULL)
		return (NULL);
	command = ft_split(cmd, ' ');
	paths = ft_split(env_value, ':');
	free(env_value);
	path = join_path(paths, command[0]);
	if (path)
		return (ft_free(paths), ft_free(command), path);
	return (ft_free(paths), ft_free(command), NULL);
}
