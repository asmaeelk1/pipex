/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:37:27 by asel-kha          #+#    #+#             */
/*   Updated: 2024/03/15 03:44:20 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*rtn;
	int		i;
	int		e;

	e = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	rtn = malloc(ft_strlen(s1) + ft_strlen(s2) + e * sizeof(char));
	if (!rtn)
		return (NULL);
	while (s1[i])
		rtn[e++] = s1[i++];
	i = 0;
	while (s2[i])
		rtn[e++] = s2[i++];
	rtn[e] = '\0';
	return (rtn);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	if ((int)size < 0 || (int)count < 0)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < (count * size))
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	e;
	char	*str;
	char	*tofind;

	str = (char *)haystack;
	tofind = (char *)needle;
	i = 0;
	if (needle[0] == '\0')
		return (str);
	while (i < len && str[i])
	{
		if (tofind[0] == str[i])
		{
			e = 0;
			while ((tofind[e] == str[i + e]) && tofind[e] && i + e < len)
				e++;
			if (tofind[e] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	return (ptr);
}
