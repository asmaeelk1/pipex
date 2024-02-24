/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:20:34 by asel-kha          #+#    #+#             */
/*   Updated: 2024/02/19 16:58:31 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	res = malloc(len +1);
	if (!res)
		return (NULL);
	while (s[start] && i < len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

static int	countwords(const char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			count++;
		if (str[i] != c && str[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static void	ft_free(char **str, int c)
{
	while (c >= 0)
	{
		free(str[c]);
		c--;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	int			l;
	int			r;
	int			e;
	char		**res;

	i = 0;
	e = 0;
	if (!s)
		return (NULL);
	res = ft_calloc((countwords(s, c) + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (s[i] && e < countwords((char *)s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		l = i;
		while (s[i] && s[i] != c)
			r = ++i ;
		res[e] = ft_substr(s, l, r - l);
		if (!res[e++])
			return (ft_free(res, e), NULL);
	}
	return (res);
}
