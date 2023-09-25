/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:48:03 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/25 23:47:09 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	_deep_free(char **buf1, char **buf2, char **buf3)
{
	if (buf1 && *buf1)
	{
		free(*buf1);
		*buf1 = NULL;
	}
	if (buf2 && *buf2)
	{
		free(*buf2);
		*buf2 = NULL;
	}
	if (buf3 && *buf3)
	{
		free(*buf3);
		*buf3 = NULL;
	}
}

char	*_update_buf(char *buf_save)
{
	char	*ret;
	int		i;

	i = 0;
	if (!buf_save)
		return (NULL);
	while (buf_save[i] && buf_save[i] != '\n')
		i++;
	if (buf_save[i] == '\n')
		i++;
	ret = ft_strdup(buf_save + i);
	_deep_free(&buf_save, NULL, NULL);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*_extract_one_line(char *buf_save)
{
	char			*line;
	int				len;
	unsigned long	addr_newline;

	if (!buf_save || *buf_save == '\0')
		return (NULL);
	addr_newline = (unsigned long)ft_strchr(buf_save, '\n');
	if (!addr_newline)
		return (ft_strdup(buf_save));
	len = (int)(addr_newline - (unsigned long)buf_save + 1);
	line = (char *)malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	line[len--] = '\0';
	while (len >= 0)
	{
		line[len] = buf_save[len];
		len--;
	}
	return (line);
}

char	*_read_to_buf(int fd, char *buf_save)
{
	char	*str;
	char	*tmp;
	size_t	read_bytes;

	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	while (!buf_save || !ft_strchr(buf_save, '\n'))
	{
		read_bytes = read(fd, str, BUFFER_SIZE);
		if ((int)read_bytes < 0)
		{
			_deep_free(&str, &buf_save, NULL);
			return (NULL);
		}
		if (read_bytes == 0)
			break ;
		*(str + read_bytes) = '\0';
		tmp = ft_strjoin(buf_save, str);
		_deep_free(&buf_save, NULL, NULL);
		buf_save = tmp;
	}
	_deep_free(&str, NULL, NULL);
	return (buf_save);
}

char	*get_next_line(int fd)
{
	static char	*buf_save = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf_save = _read_to_buf(fd, buf_save);
	if (!buf_save)
		return (NULL);
	line = _extract_one_line(buf_save);
	if (!line || *line == '\0')
	{
		_deep_free(&line, &buf_save, NULL);
		return (NULL);
	}
	buf_save = _update_buf(buf_save);
	if (!buf_save)
		return (NULL);
	return (line);
}
