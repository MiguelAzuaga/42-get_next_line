/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueiros <mqueiros@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:09:06 by jdecorte          #+#    #+#             */
/*   Updated: 2025/05/08 17:28:00 by mqueiros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strndup(const char *str, size_t len)
{
	char	*dst;
	size_t	i;

	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_strjoin_free(char *s1, char *s2, size_t s2_len)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	char	*dst;

	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	dst = malloc(s1_len + s2_len + 1);
	if (!dst)
	{
		free(s1);
		return (NULL);
	}
	while (i < s1_len)
		dst[i++] = s1[j++];
	j = 0;
	while (j < s2_len && s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	free(s1);
	return (dst);
}

ssize_t	ft_charpos(char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_read_line(int fd, char *buffer, char *line)
{
	ssize_t	bytes_read;
	ssize_t	nl;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free_gnl(line));
		else
			buffer[bytes_read] = '\0';
		nl = ft_charpos(buffer, '\n');
		if (nl >= 0)
		{
			line = ft_strjoin_free(line, buffer, nl + 1);
			ft_memmove(buffer, buffer + nl + 1, ft_strlen(buffer + nl + 1));
			buffer[ft_strlen(buffer + nl + 1)] = '\0';
			return (line);
		}
		line = ft_strjoin_free(line, buffer, bytes_read);
	}
	if (line && line[0])
		return (line);
	return (ft_free_gnl(line));
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (buffer[0])
	{
		nl = ft_charpos(buffer, '\n');
		if (nl >= 0)
		{
			line = ft_strndup(buffer, nl + 1);
			ft_memmove(buffer, buffer + nl + 1, ft_strlen(buffer + nl + 1));
			buffer[ft_strlen(buffer + nl + 1)] = '\0';
			return (line);
		}
		line = ft_strjoin_free(line, buffer, ft_strlen(buffer));
		buffer[0] = '\0';
	}
	return (ft_read_line(fd, buffer, line));
}
