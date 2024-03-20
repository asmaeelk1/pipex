/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:40 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/20 09:46:19 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*split_nl(char **save)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	tmp = *save;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	line = ft_substr(*save, 0, i + 1);
	if (tmp[i] == '\n')
		i++;
	*save = ft_strdup(tmp + i);
	return (free(tmp), line);
}

char	*read_line(int fd, char *save)
{
	char	*buff;
	int		readret;
	char	*tmp;

	save = ft_calloc(1, 1);
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff || !save)
		return (NULL);
	buff[0] = 0;
	readret = 1;
	while (readret && !ft_strchr(save, '\n'))
	{
		readret = read(fd, buff, BUFFER_SIZE);
		if (readret == -1)
			return (free(buff), free(save), NULL);
		buff[readret] = '\0';
		tmp = ft_strjoin(save, buff);
		if (!tmp)
			return (free(buff), free(save), NULL);
		free(save);
		save = tmp;
	}
	if (readret == 0 && save[0] == '\0')
		return (free(buff), free(save), NULL);
	return (free(buff), save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*str;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	save = read_line(fd, save);
	if (!save)
		return (NULL);
	str = split_nl(&save);
	free(save);
	return (str);
}
