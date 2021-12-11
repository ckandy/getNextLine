/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckandy <ckandy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:32:15 by ckandy            #+#    #+#             */
/*   Updated: 2021/12/10 13:56:53 by ckandy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_slice(char *st)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (st[i] && st[i] != '\n')
		i++;
	if (!st[i])
	{
		free(st);
		return (0);
	}
	str = malloc(sizeof(char) * (ft_strlen(st) - i + 1));
	if (!str)
		return (0);
	j = 0;
	i++;
	while (st[i])
	{
		str[j++] = st[i++];
	}
	str[j] = '\0';
	free(st);
	return (str);
}

char	*ft_wr(char *st)
{
	int		i;
	char	*str;

	i = 0;
	if (st[i] == '\0')
		return (0);
	while (st[i] && st[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (0);
	i = 0;
	while (st[i] && st[i] != '\n')
	{
		str[i] = st[i];
		i++;
	}
	if (st[i] == '\n')
	{
		str[i] = st[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_write_str(int fd, char *str)
{
	char	*buf;
	int		i;

	i = 1;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	while (!ft_search_str(str) && i != 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*string;
	static char	*st[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	st[fd] = ft_write_str(fd, st[fd]);
	if (!st[fd])
		return (0);
	string = ft_wr(st[fd]);
	st[fd] = ft_slice(st[fd]);
	return (string);
}
