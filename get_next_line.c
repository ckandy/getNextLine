/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckandy <ckandy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:30:49 by ckandy            #+#    #+#             */
/*   Updated: 2021/12/10 13:48:52 by ckandy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_slice(char *str)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	string = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!string)
		return (0);
	j = 0;
	i++;
	while (str[i])
	{
		string[j++] = str[i++];
	}
	string[j] = '\0';
	free(str);
	return (string);
}

char	*ft_wr(char *str)
{
	int		i;
	char	*string;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	string = malloc(sizeof(char) * (i + 2));
	if (!string)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		string[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		string[i] = str[i];
		i++;
	}
	string[i] = '\0';
	return (string);
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
	char		*str;
	static char	*st;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	st = ft_write_str(fd, st);
	if (!st)
		return (0);
	str = ft_wr(st);
	st = ft_slice(st);
	return (str);
}
