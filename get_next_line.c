/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:48:03 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/25 18:07:41 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*_update_buf(char *buf_save)
{
	char	*ret;
	int		i;

	i = 0;
	while (buf_save[i] && buf_save[i] != '\n')
		i++;
	
	ret = ft_strdup(buf_save + i + 1);
	free(buf_save);
	return (ret);
}

char	*_extract_one_line(char *buf_save)
{
	char			*line;
	int				len;
	unsigned long	addr_newline;

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

	if (buf_save && ft_strchr(buf_save, '\n'))
		return (buf_save);
	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	while (!buf_save || !ft_strchr(buf_save, '\n'))
	{
		read_bytes = read(fd, str, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(str);
			return (NULL);
		}
		if (read_bytes == 0)
			break ;
		*(str + read_bytes) = '\0';
		tmp = ft_strjoin(buf_save, str);
		free(buf_save);
		buf_save = tmp;
	}
	free(str);
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
	{
		free(buf_save);
		return (NULL);
	}
	line = _extract_one_line(buf_save);
	buf_save = _update_buf(buf_save);
	return (line);
}
